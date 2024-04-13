//File:CS112_A3_Part2B_S11_20231047_20230528_20231179
//Purpose:MiniPhotoshop program
//Authors: HassanMomen|| ShahdAyman|| Menna Mustafa
//IDS: 
//Hassan Momen 20231047 - (Menu/BW filter/Mirroring image/cropping Filter/Resizing filter/Saving function/Load function)
// Shahd Ayman 20230528 - (GrayScale filter/Merge filter/Brightness Filter/Edge Detection filter)
// Menna Mustafa 20231179 - (Invert colors filter / rotate filter)
//Repo link on git-hub: https://github.com/7axzn/MiniPhotoshop
// Emails:
// Hassan Momen:hasanmomen2005@gmail.com
// Shahd Ayman:shahdayman2003@gmail.com.
// Menna Mustafa:mennam.anter8973@gmail.com. 



// Bonus:
// Hassan (Infrared filter,Sunlight filter)
// Shahd (Purple filter)

#include <iostream>
#include <string>
#include "Image_Class.h"
using namespace std;

//HassanMomen -20231047

//Function to save images
void Saving(Image input,string Origname)
{
    cout << "Do you want to save the photo or edit the original?" << endl;
        cout << "1) Save the photo" << endl;
        cout << "2) Edit the original" << endl;
        cout << "Enter your choice: ";
        char ans2;
        cin >> ans2;

        // Validate input 
        while (ans2 != '1' && ans2 != '2') {
            cout << "Invalid choice. Please enter a valid option (1 or 2): ";
            cin >> ans2;
        }

        if (ans2 == '1') {
            // Prompt for filename and extension
            cout << "Enter the filename for the new file (without extension): ";
            string name;
            cin >> name;

            cout << "Choose an extension:" << endl;
            cout << "1) JPEG" << endl;
            cout << "2) JPG" << endl;
            cout << "3) PNG" << endl;
            cout << "4) BMP" << endl;
            cout << "Enter your choice: ";
            char extension;
            cin >> extension;

            // Validate extension choice
            while (extension != '1' && extension != '2' && extension != '3' && extension != '4') {
                cout << "Invalid choice. Please enter a valid option (1, 2, 3, or 4): ";
                cin >> extension;
            }

            // Save the image with the selected extension
            if (extension == '1') {
                name += ".jpeg";
            } else if (extension == '2') {
                name += ".jpg";
            } else if (extension == '3') {
                name += ".png";
            } else if (extension == '4') {
                name += ".bmp";
            }
            input.saveImage(name);
        } else if (ans2 == '2') {
            input.saveImage(Origname);
        }
}


//Function to load an image file for editing
string load() {
    cout << "Load the image to edit!" << endl;
    cout << "TYPE THE FILENAME WITH THE EXTENSION TO WORK: ";
    string file_n;
    cin >> file_n;
    try {
        // Try to create an Image object with the provided filename
        Image image(file_n);
    } catch (const exception& e) {
        // If  file not found , recursively call load() again
        cout << "Error: File not found. Please make sure the file exists and try again." << endl;
        file_n = load();
    }
    return file_n;
}


//Function to insert the 2nd merged image 
string load2() {
    cout << "Load the image you want to merge with the first one!" << endl;
    cout << "TYPE THE FILENAME WITH THE EXTENSION TO WORK: ";
    string file_n2;
    cin >> file_n2;
    try {
        // Try to create an Image object with the provided filename
        Image image(file_n2);
    } 
    catch (const exception& e) 
    {
        // If  file not found , recursively call load() again
        cout << "Error: File not found. Please make sure the file exists and try again." << endl;
        file_n2 = load2();
    }
    return file_n2;
}



// Function to convert an image to black and white

void BW(Image& input,string Origname) {
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
                if (avg_inten > 128)  input(i, j, k) = 255;
                   
                else  input(i, j, k) = 0;
                   
            }
        }
    }
    Saving(input,Origname);
}


// Function to horizontally mirror an image

void HorizontalMir(Image& input, string Origname) {
    // Iterate over each pixel in the image
    for (int i = 0; i < input.width; i++) {
        for (int j = 0; j < input.height; j++) {
            // Iterate over each color channel (RGB)
            for (int k = 0; k < 3; k++) {
                // Flip the pixel horizontally
                input(i, j, k) = input(input.width - 1 - i, j, k);
            }
        }
    }
    // Save the horizontally mirrored image
    Saving(input, Origname);
}


// Function to vertically mirror an image

void VerticalMirror(Image& input, string Origname) {
    // Iterate over each pixel in the image
    for (int i = 0; i < input.width; i++) {
        for (int j = 0; j < input.height; j++) {
            // Iterate over each color channel (RGB)
            for (int k = 0; k < 3; k++) {
                // Flip the pixel vertically
                input(i, j, k) = input(i, input.height - 1 - j, k);
            }
        }
    }
    // Save the vertically mirrored image
    Saving(input, Origname);
}

// Function to crop an image

void crop(Image input, string Origname) {
    int widthStart, heightStart, width, height;

    // Prompt the user to enter coordinates for cropping
    cout << "Enter the coordinates to start from:\n";
    cout << "Width:\n";
    cin >> widthStart;
    cout << "Height:\n";
    cin >> heightStart;

    // Validate the entered coordinates
    while (widthStart > input.width || heightStart > input.height) {
        cout << "Invalid coordinates! Please enter valid coordinates:\n";
        cout << "Width:\n";
        cin >> widthStart;
        cout << "Height:\n";
        cin >> heightStart;
    }

    // Prompt the user to enter dimensions for the new image
    cout << "Enter dimensions for the new image:\n";
    cout << "Width:\n";
    cin >> width;
    cout << "Height:\n";
    cin >> height;


    // Validate the entered dimensions
    while (width > input.width || height > input.height) {
        cout << "Invalid dimensions! Please enter valid dimensions:\n";
        cout << "Width:\n";
        cin >> width;
        cout << "Height:\n";
        cin >> height;
    }

    // Create a new image with the specified dimensions
    Image crop(width, height);

    // Copy pixels from the original image to the cropped image
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            for (int k = 0; k < 3; k++) {
                crop(i, j, k) = input(i + widthStart, j + heightStart, k);
            }
        }
    }
    // Save the cropped image
    Saving(crop, Origname);
}

// Function to resize an image
void resize(Image img, string origname)
{
    int width, height;
    
    // Prompt user to input new image dimensions
    cout << "Insert the new image dimensions\n";
    cout << "Width: ";
    cin >> width;
    cout << "Height: ";
    cin >> height;

    // Create a new image  with the specified dimensions
    Image resized(width, height);

    // Calculate scaling factors for resizing
    double factorH = img.height / height;
    double factorW = img.width / width;

    // Iterate through each pixel in the new image
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            for (int k = 0; k < 3; k++) {
                // make new pixel based on the scaling factors and round it to the nearest integer
                resized(i, j, k) = round(img(i * factorW, j * factorH, k));
            }
        }
    }

    // Save the resized image
    Saving(resized, origname);
}


// Function to apply an infrared effect to an image
void infrared(Image input, string Origname) {
    // Iterate through each pixel in the image
    for (int i = 0; i < input.width; i++) {
        for (int j = 0; j < input.height; j++) {
            // Set the red channel to its maximum value (255)
            input(i, j, 0) = 255;
            // Subtract the green and blue channels from 255
            input(i, j, 1) = 255 - input(i, j, 1);
            input(i, j, 2) = 255 - input(i, j, 2);
        }
    }
    // Save the modified image
    Saving(input, Origname);
}


    
// Function to apply a sun effect to an image
void Sun(Image img, string Origname)
{
    // Iterate through each pixel in the image
    for (int i = 0; i < img.width; i++)
    {
        for (int j = 0; j < img.height; j++)
        {
            // Increase the intensity of the red and green channels by multiplying by 1
            img(i, j, 0) *= 1; 
            img(i, j, 1) *= 1; 
            
            // Decrease the intensity of the blue channel by multiplying by 0.7
            img(i, j, 2) *= 0.7; 
        }
    }

    // Save the modified image
    Saving(img, Origname);
}


//////////////////////////////////////////////////////////////////////////////
//ShahdAyman -20230528

// Function to convert an image to grayscale
void Grayscale(Image& input,string Origname) {
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
    Saving(input,Origname);
}


void Merge(Image &image1,  Image & image2,string Origname) {
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
    Saving(image1,Origname);

}

// Function to adjust the brightness of the image by a factor
void adjustBrightness(Image& img, float factor,string origname) {
    for (int y = 0; y < img.height; ++y) {
        for (int x = 0; x < img.width; ++x) {
            for (int c = 0; c < img.channels; ++c) {
                unsigned char& pixelValue = img(x, y, c);
                pixelValue = static_cast<unsigned char>(pixelValue * factor);
            }
        }
    }
    Saving (img,origname);
}

void EdgeDetection(Image input,string Origname) {

    Image edgeDetectedImage(input.width, input.height);

    // Define Sobel kernel matrices for gradient calculation
    int sobelX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int sobelY[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int y = 1; y < input.height - 1; ++y) {
        for (int x = 1; x < input.width - 1; ++x) {
            // Calculate the gradient in x and y directions using the Sobel operator
            float gradientX = 0, gradientY = 0;
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    for (int c = 0; c < input.channels; ++c) {
                        gradientX += input.getPixel(x + j, y + i, c) * sobelX[i + 1][j + 1];
                        gradientY += input.getPixel(x + j, y + i, c) * sobelY[i + 1][j + 1];
                    }
                }
            }

            // Calculate the gradient magnitude
            float gradientMagnitude = sqrt(gradientX * gradientX + gradientY * gradientY);

            if (gradientMagnitude > 50) { 
                // Set the pixel in the edge-detected image to white
                for (int c = 0; c < edgeDetectedImage.channels; ++c) {
                    edgeDetectedImage.setPixel(x, y, c, 255);
                }
            } else {
                // Set the pixel in the edge-detected image to black
                for (int c = 0; c < edgeDetectedImage.channels; ++c) {
                    edgeDetectedImage.setPixel(x, y, c, 0);
                }
            }
        }
    }
        Saving(edgeDetectedImage,Origname);
}

void purple(Image inputImage,string Origname) {

        const int purpleTint = 30;
        // Apply the purple tint to each pixel of the entire image
        for (int y = 0; y < inputImage.height; ++y) {
            for (int x = 0; x < inputImage.width; ++x) {
                unsigned char r = inputImage(x, y, 0);
                unsigned char g = inputImage(x, y, 1);
                unsigned char b = inputImage(x, y, 2);

                // Increase the intensity of red and blue channels to apply the purple tint
                inputImage(x, y, 0) = min(255, r + purpleTint); // Red channel
                inputImage(x, y, 1) = min(255, g + purpleTint / 2); // Green channel
                inputImage(x, y, 2) = min(255, b + purpleTint); // Blue channel
            }
        }
        Saving(inputImage,Origname);
}

//////////////////////////////////////////////////////////
//Menna Mustafa 20231179

// Function to invert colors of an image
void invertColors(Image &img,string Origname) {
    // Loop through each pixel row
    for (int j = 0; j < img.height; ++j) {
        // Loop through each pixel column
        for (int i = 0; i < img.width; ++i) {
            // Loop through each color channel (RGB)
            for (int k = 0; k < 3; ++k) {
                // Invert color channel value
                img(i, j, k) = 255 - img(i, j, k);
            }
        }
    }
        Saving(img,Origname);
}


// Function to rotate an image by 90 degrees clockwise
void rotate90save(Image &img, string Origname) {
    int width = img.width;
    int height = img.height;

    // Create a new image with dimensions swapped for rotation
    Image rotated_img(height, width);

    // Iterate through each pixel in the original image
    for (int y = 0; y < width; ++y) {
        for (int x = 0; x < height; ++x) {
            for(int k = 0; k < 3; k++) {
                // Rotate the pixel and assign it to the corresponding position in the rotated image
                rotated_img(height - 1 - x, y, k) = img(y, x, k);
            }
        }
    }

    Saving(rotated_img, Origname);
}


void rotate90(Image &img) {
    int width = img.width;
    int height = img.height;

    // Create a new image with dimensions swapped for rotation
    Image rotated_img(height, width);

    // Iterate through each pixel in the original image
    for (int y = 0; y < width; ++y) {
        for (int x = 0; x < height; ++x) {
            for(int k = 0; k < 3; k++) {
                // Rotate the pixel and assign it to the corresponding position in the rotated image
                rotated_img(height - 1 - x, y, k) = img(y, x, k);
            }
        }
    }
}


// Function to rotate image by 180 degrees clockwise
void rotate180(Image &img, string Origname) {
    // Rotate by 90 degrees twice
    rotate90(img);
    rotate90save(img, Origname); // Save after two rotations
}

// Function to rotate image by 270 degrees clockwise
void rotate270(Image &img, string Origname) {
    // Rotate by 90 degrees three times
    rotate90(img);
    rotate90(img);
    rotate90save(img, Origname); // Save after three rotations
}
/////////////////////////////////////////////////////////////////////////////////////////////////////

int menu()
{
    // Load image
    string file_n = load();
    Image File_ph(file_n);

    // Apply filter
    cout << "SELECT A FILTER TO APPLY:" << endl;
    cout << "1) Black and white" << endl;
    cout << "2) GrayScale" << endl;
    cout << "3) Merge 2 images" << endl;
    cout << "4) Invert color" << endl;
    cout << "5) Rotate image" << endl;
    cout << "6) Resize image" << endl;
    cout << "7) Crop image" << endl;
    cout << "8) Brightness adjust" << endl;
    cout << "9) Mirror image" << endl;
    cout << "10) Infrared filter" << endl;
    cout << "11) Sunlight filter" << endl;
    cout << "12) Edge Detection filter" << endl;
    cout << "13) Purple Filter" << endl;
    cout << "Enter your choice: ";
    int ans;
    cin >> ans;
    
    // Validate input 
    while (ans < 1 || ans > 13) {
        cout << "Invalid choice. Please enter a valid option: ";
        cin >> ans;
    }

    // Apply filter based on user choice
    if (ans == 1) {
        BW(File_ph, file_n);
    } else if (ans == 2) {
        Grayscale(File_ph, file_n);
    } else if (ans == 3) {
        string file_n2 = load2();
        Image File_ph2(file_n2);
        Merge(File_ph, File_ph2, file_n);
    } else if (ans == 4) {
        invertColors(File_ph, file_n);
    } else if (ans == 5) {
        cout << "How do you want to rotate?" << endl;
        cout << "1) 90 Degrees" << endl;
        cout << "2) 180 Degrees" << endl;
        cout << "3) 270 Degrees" << endl;
        char ans4;
        cin >> ans4;
        while (ans4 < '1' || ans4 > '3') {
            cout << "Invalid choice. Please enter a valid option: ";
            cin >> ans4;
        }
        if (ans4 == '1')
            rotate90save(File_ph, file_n);
        else if (ans4 == '2')
            rotate180(File_ph, file_n);
        else if (ans4 == '3')
            rotate270(File_ph, file_n);
    } else if (ans == 6) {
        resize(File_ph, file_n);
    } else if (ans == 7) {
        crop(File_ph, file_n);
    } else if (ans == 8) {
        float factor;
        cout << "Insert the amount to adjust brightness (0,1): ";
        cin >> factor;
        adjustBrightness(File_ph, factor, file_n);
    } else if (ans == 9) {
        cout << "1) Vertical" << endl;
        cout << "2) Horizontal" << endl;
        char ans5;
        cin >> ans5;
        if (ans5 == '1') 
            VerticalMirror(File_ph, file_n);
        else if (ans5 == '2')
            HorizontalMir(File_ph, file_n);
    } else if (ans == 10) {
        infrared(File_ph, file_n);
    } else if (ans == 11) {
        Sun(File_ph, file_n);
    } else if (ans == 12) {
        EdgeDetection(File_ph, file_n);
    } else if (ans == 13) {
        purple(File_ph, file_n);
    }

    // Ask the user if they want to continue
    cout << "Do you want to continue? (Press Q to exit): ";
    string ans3;
    cin >> ans3;
    if (ans3 != "Q" && ans3 != "q") {
        menu();
    }

    return 0;
}


int main() {
    menu();
    return 0;
}


