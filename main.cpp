/* Code compiles and runs on VS CODE using the terminal with the command ./main pixels.dat
if any errors happen just click the "run code" and then type the previous command in terminal */
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "pixel.h"

// Vector to store pixels
std::vector<Pixel> pixel_list;

void read_pixel_data(const std::string& filename, std::vector<Pixel>& pixel_list) {
    std::ifstream infile(filename);
    std::string line;

    while (std::getline(infile, line)) {
        std::stringstream ss(line);
        std::string x_str, y_str, r_str, g_str, b_str;

        // Parse each value separated by a comma
        std::getline(ss, x_str, ',');
        std::getline(ss, y_str, ',');
        std::getline(ss, r_str, ',');
        std::getline(ss, g_str, ',');
        std::getline(ss, b_str, ',');

        // Convert strings to appropriate types
        Pixel p;
        p.x = std::stoi(x_str);
        p.y = std::stoi(y_str);
        p.r = std::stof(r_str);
        p.g = std::stof(g_str);
        p.b = std::stof(b_str);

        // Add the pixel to the list
        pixel_list.push_back(p);
    }

    infile.close();
}

void average_colors(std::vector<Pixel>& pixel_list) {
    float r_sum = 0.0f, g_sum = 0.0f, b_sum = 0.0f;
    int count = pixel_list.size();

    for (const Pixel& p : pixel_list) {
        r_sum += p.r;
        g_sum += p.g;
        b_sum += p.b;
    }

    float r_avg = r_sum / count;
    float g_avg = g_sum / count;
    float b_avg = b_sum / count;

    std::cout << "Average R: " << r_avg << "\n";
    std::cout << "Average G: " << g_avg << "\n";
    std::cout << "Average B: " << b_avg << "\n";
}

void flip_vertically(std::vector<Pixel>& pixel_list) {
    int max_y = 255;  
    for (Pixel& p : pixel_list) {
        p.y = max_y - p.y;
    }
}

void save_flipped_data(const std::string& filename, const std::vector<Pixel>& pixel_list) {
    std::ofstream outfile(filename);
    for (const Pixel& p : pixel_list) {
        outfile << p.x << "," << p.y << "," << p.r << "," << p.g << "," << p.b << "\n";
    }

    outfile.close();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::vector<Pixel> pixel_list;

    // Read the pixel data from the file
    read_pixel_data(filename, pixel_list);

    // Calculate the average colors
    average_colors(pixel_list);

    // Flip the image vertically
    flip_vertically(pixel_list);

    // Save the flipped data to a file
    save_flipped_data("flipped.dat", pixel_list);

    return 0;
}