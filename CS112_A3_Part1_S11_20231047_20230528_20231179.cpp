//File:CS112_A3_Part1_S11_20231047_20230528_20231179
//Purpose:MiniPhotoshop program
//Authors: HassanMomen|| ShahdAyman|| Menna Mustafa
//IDS: 
//Hassan Momen 20231047 - (Menu/BW filter)
// Shahd Ayman 20230528 - (GrayScale filter/Merge filter)
// Menna Mustafa 20231179 - ()

#include <iostream>
#include <string>
#include "Image_Class.h"
using namespace std;
//HassanMomen -20231047

//Function to load an image file for editing
string load() {
    cout << "Load the image to edit!\n-TYPE THE FILENAME WITH THE EXTENSION TO WORK!\n";
    string file_n;
    cin >> file_n;
    try {
        // Try to create an Image object with the provided filename
        Image image(file_n);
    } catch (const exception& e) {
        // If an exception occurs (e.g., file not found), recursively call load() again
        file_n = load();
    }
    return file_n;
}

//Function to insert the 2nd merged image 
string load2() {
    cout << "Load the image you want to merge with the first one!\n-TYPE THE FILENAME WITH THE EXTENSION TO WORK!\n";
    string file_n2;
    cin >> file_n2;
    try {
        // Try to create an Image object with the provided filename
        Image image(file_n2);
    } catch (const exception& e) {
        // If an exception occurs (e.g., file not found), recursively call load() again
        file_n2 = load();
    }
    return file_n2;
}


// Function to convert an image to black and white
void BW(Image& input) {
    // Iterate over each pixel in the image
    for (int i = 0; i < input.width; i++) {
        for (int j = 0; j < input.height; j++) {
            // Initialize variable to store the average intensity of RGB
            unsigned int avg_inten = 0;
            // Calculate the average intensity by summing up the intensity of each RGB channel
            for (int k = 0; k < 3; k++) {
                avg_inten += input(i, j, k);
            }
            avg_inten /= 3; // Divide by 3 to get the average
            
            // Set each RGB channel of the pixel based on the average intensity
            for (int k = 0; k < 3; k++) {
                // If average intensity is greater than 128, set the channel to maxi(white),
                // otherwise set it to minimum (black)
                if (avg_inten > 128)
                    input(i, j, k) = 255;
                else
                    input(i, j, k) = 0;
            }
        }
    }
}






//////////////////////////////////////////////////////////////////////////////
//ShahdAyman -20230528

// Function to convert an image to grayscale
void Grayscale(Image& input) {
    // Iterate over each row of the image
    for (int y = 0; y < input.height; ++y) {
        // Iterate over each column of the image
        for (int x = 0; x < input.width; ++x) {

            // Retrieve the  components of the current pixel
            unsigned char R = input.getPixel(x, y, 0);  
            unsigned char G = input.getPixel(x, y, 1);  
            unsigned char B = input.getPixel(x, y, 2);  
            
            // Convert RGB to grayscale using weighted average method
            unsigned char gray = (unsigned char)(0.299 * R + 0.587 * G + 0.114 * B);

            // Set grayscale value for each color channel of the current pixel
            input.setPixel(x, y, 0, gray);  
            input.setPixel(x, y, 1, gray);  
            input.setPixel(x, y, 2, gray);  
        }
    }
}
void Merge(Image &image1,  Image & image2) {
    // Find the maximum width and height to ensure we iterate over the smaller image
    int maxWidth = min(image1.width, image2.width);
    int maxHeight = min(image1.height, image2.height);

    // Iterate over each pixel in the height of image1
    for (int y = 0; y < image1.height; ++y) {
        // Iterate over each pixel in the width of image1
        for (int x = 0; x < image1.width; ++x) {
            // Check if the current pixel is within the bounds of both images
            if (x < maxWidth && y < maxHeight) {
                // Iterate over each channel (e.g., RGB)
                for (int c = 0; c < image1.channels; ++c) {
                    // Blend pixel values from both images and assign to image1
                    image1(x, y, c) = (image1(x, y, c) + image2(x, y, c)) / 2;
                }
            }
        }
    }
}





int main() {
    do {
        string file_n = load();

        // Load image
        Image File_ph(file_n);

        // Apply filter
        cout << "SELECT A FILTER TO APPLY:\n1) Black and white\n2) GrayScale\n3) Merge 2 images\n";
        char ans;
        cin >> ans;
        
        // Validate  input 
        while (ans != '1' && ans != '2'&& ans != '3') {
            cout << "Please insert a valid choice!\n";
            cin >> ans;
        }

        // Apply  filter
        if (ans == '1') {
            BW(File_ph); 
        } else if (ans == '2') {
            Grayscale(File_ph); 
        }
         else if (ans == '3') {
            string file_n2 = load2();
            Image File_ph2(file_n2);
            Merge(File_ph,File_ph2);

        }

        // ask user save or edit the original image
        cout << "Do you want to save the photo or edit the original?\n";
        cout << "1) Save the photo \n2) Edit the original\n";
        char ans2;
        cin >> ans2;

        // Validate  input 
        while (ans2 != '1' && ans2 != '2') {
            cout << "Please insert a valid choice!\n";
            cin >> ans2;
        }

        if (ans2 == '1') {
            // ask user for new filename and extension
            cout << "What do you want to name the new file? (without the extension)\n";
            string name;
            cin >> name;

            char extension;
            cout << "Choose an extension:\n1) JPEG\n2) JPG\n3) PNG\n4) BMP\n";
            cin >> extension;

            // Validate  input for extension choice
            while (extension != '1' && extension != '2' && extension != '3' && extension != '4') {
                cout << "Please insert a valid choice!\n";
                cin >> extension;
            }

            // Save the  image with the extension
            if (extension == '1') {
                name += ".jpeg";
            } else if (extension == '2') {
                name += ".jpg";
            } else if (extension == '3') {
                name += ".png";
            } else if (extension == '4') {
                name += ".bmp";
            }

          
            File_ph.saveImage(name);
        } else if (ans2 == '2') {
           
            File_ph.saveImage(file_n);
        }

        // Ask the user if they want to continue
        cout << "Do you want to continue? (Press Q to exit)\n";
        string ans3;
        cin >> ans3;
        if (ans3 == "Q" || ans3 == "q") {
            break; 
        }
    } while (true); 

    return 0;
}
