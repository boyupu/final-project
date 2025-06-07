#include "image_encryption.h"
#include "rgb_image.h"
#include "gray_image.h"
#include <sstream>
#include <algorithm>

// Constructor implementations
ImageEncryption::ImageEncryption() {
    password = "";
}

ImageEncryption::ImageEncryption(string Pass) {
    password = Pass;
}

string ImageEncryption::getPassword() {
    return password;
}

// Convert single character to 8-bit binary string
string ImageEncryption::char_to_binary(char c) {
    bitset<8> binary(c);
    return binary.to_string();
}

// Convert entire string to binary stream
string ImageEncryption::string_to_binary_stream(const string& message) {
    string binary_stream = "";
    for (char c : message) {
        binary_stream += char_to_binary(c);
    }
    // Add delimiter to mark end of message
    binary_stream += "11111111"; // EOF marker
    return binary_stream;
}

//==========================================================================
// Encrypt message into RGB image using LSB steganography
RGBImage* ImageEncryption::encrypt_RGBImage(RGBImage* img) {
    
    // Create message from password
    string message = "ENCRYPTED:" + password;
    string binary_data = string_to_binary_stream(message);
    
    int width = img->getWidth();
    int height = img->getHeight();
    int bit_index = 0;
    int capacity = width * height * 3; //
    
    if (binary_data.length() > capacity) {
        cerr << "ERROR: THIS SENTENCE IS TOO LONG!" << endl;
        return nullptr;
    }
    
    int*** new_pixels = new int**[height];
    for (int y = 0; y < height; ++y) {
        new_pixels[y] = new int*[width];
        for (int x = 0; x < width; ++x) {
            new_pixels[y][x] = new int[3];
            for (int c = 0; c < 3; ++c) {
                new_pixels[y][x][c] = img->getrgbpix(x, y, c);
            }
        }
    }
    
    
    for (int y = 0; y < height && bit_index < binary_data.length(); y++) {
        for (int x = 0; x < width && bit_index < binary_data.length(); x++) {
            for (int c = 0; c < 3 && bit_index < binary_data.length(); c++) {
                int pixel_value = new_pixels[y][x][c];
                pixel_value = (pixel_value & 0xFE); // 11111110
                if (binary_data[bit_index] == '1') {
                    pixel_value |= 1;
                }
                new_pixels[y][x][c] = pixel_value;
                bit_index++;
            }
        }
    }

    return new RGBImage(width, height, new_pixels);
}


//==========================================================================
// Encrypt message into grayscale image using LSB steganography
GrayImage* ImageEncryption::encrypt_GrayImage(GrayImage* img) {
    
    // Create message from password
    string message = "ENCRYPTED:" + password;
    string binary_data = string_to_binary_stream(message);
    
    int width = img->getWidth();
    int height = img->getHeight();
    int bit_index = 0;
    int capacity = width * height * 3; //
    
    if (binary_data.length() > capacity) {
        cerr << "ERROR: THIS SENTENCE IS TOO LONG!" << endl;
        return nullptr;
    }
    
    int** new_pixels = new int*[height];
    for (int y = 0; y < height; ++y){
        new_pixels[y] = new int[width];
        for(int x = 0 ; x < width ; x++){
        
          new_pixels[y][x] = img->getPixel(x, y);
 
        }
    }
    
    for (int y = 0; y < height && bit_index < binary_data.length(); y++) {
        for (int x = 0; x < width && bit_index < binary_data.length(); x++) {
            int pixel_value = new_pixels[y][x];
            pixel_value = (pixel_value & 0xFE);
            if (binary_data[bit_index] == '1') {
                pixel_value |= 1;
            }
            new_pixels[y][x] = pixel_value;
            bit_index++;
        }
    }
    
    return new GrayImage(width, height, new_pixels);
}


//==========================================================================
// Decrypt message from RGB image
string ImageEncryption::decrypt_RGBImage(RGBImage* img) {
        if (!img) {
        cerr << "ERROR: This is a nullptr." << endl;
        return "";
    }
    
    int width = img->getWidth();
    int height = img->getHeight();
    string binary_data = "";
    
    // Extract LSBs from RGB channels
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            for (int channel = 0; channel < 3; channel++) {
                int pixel_value = img->getrgbpix(x, y, channel);
                binary_data += (pixel_value & 1) ? '1' : '0'; // Extract LSB
                
                // Check for EOF marker every 8 bits
                if (binary_data.length() >= 8 && binary_data.length() % 8 == 0) {
                    string last_byte = binary_data.substr(binary_data.length() - 8, 8);
                    if (last_byte == "11111111") { // EOF marker found
                        binary_data = binary_data.substr(0, binary_data.length() - 8);
                        goto decode_message_rgb;
                    }
                }
            }
        }
    }
    
decode_message_rgb:
    // Convert binary data back to string
    string decoded_message = "";
    for (int i = 0; i < binary_data.length(); i += 8) {
        if (i + 8 <= binary_data.length()) {
            string byte = binary_data.substr(i, 8);
            bitset<8> bits(byte);
            char c = static_cast<char>(bits.to_ulong());
            decoded_message += c;
        }
    }
    
    // Remove "ENCRYPTED:" prefix if present
    if (decoded_message.substr(0, 10) == "ENCRYPTED:") {
        return decoded_message.substr(10);
    }
    
    return decoded_message;
}


//==========================================================================
// Decrypt message from grayscale image
string ImageEncryption::decrypt_GrayImage(GrayImage* img) {
    if (!img) {
        cerr << "ERROR: This is a nullptr." << endl;
        return "";
    }
    
    int width = img->getWidth();
    int height = img->getHeight();
    string binary_data = "";
    
    // Extract LSBs from grayscale pixels
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int pixel_value = img->getPixel(x, y);
            binary_data += (pixel_value & 1) ? '1' : '0'; // Extract LSB
            
            // Check for EOF marker every 8 bits
            if (binary_data.length() >= 8 && binary_data.length() % 8 == 0) {
                string last_byte = binary_data.substr(binary_data.length() - 8, 8);
                if (last_byte == "11111111") { // EOF marker found
                    binary_data = binary_data.substr(0, binary_data.length() - 8);
                    goto decode_message_gray;
                }
            }
        }
    }
    
decode_message_gray:
    // Convert binary data back to string
    string decoded_message = "";
    for (int i = 0; i < binary_data.length(); i += 8) {
        if (i + 8 <= binary_data.length()) {
            string byte = binary_data.substr(i, 8);
            bitset<8> bits(byte);
            char c = static_cast<char>(bits.to_ulong());
            decoded_message += c;
        }
    }
    
    // Remove "ENCRYPTED:" prefix if present
    if (decoded_message.substr(0, 10) == "ENCRYPTED:") {
        return decoded_message.substr(10);
    }
    
    return decoded_message;
}
