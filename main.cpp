#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <stdlib.h>

char colors[] = {' ', '.', '-', '+', '=', '*', '$', '#'};
int levels = 8;
int dstWidth = 50;

void normalizeImage(cv::Mat &frame) {
  float ratio = (float)frame.rows / frame.cols;
  cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
  cv::equalizeHist(frame, frame);
  cv::resize(frame, frame, cv::Size(dstWidth, dstWidth * ratio));
}

void printImage(cv::Mat &frame) {
  normalizeImage(frame);
  int width = frame.cols;
  int height = frame.rows;

  int step = 255 / (levels - 1);

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      int val = frame.at<uchar>(i, j);
      int l = val / step;
      std::cout << colors[levels - 1 - l] << colors[levels - 1 - l];
    }
    std::cout << "\n";
  }
}

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "Usage: ./TerminalDrawer file\n";
    exit(EXIT_FAILURE);
  }

  std::string filename = argv[1];

  if (filename.length() < 4) {
    std::cout << "Incorrect filename\n";
    exit(EXIT_FAILURE);
  }

  std::string extension = filename.substr(filename.length() - 3);

  if (extension == "png" || extension == "jpg") {
    cv::Mat file = cv::imread(filename);
    if (file.empty()) {
      std::cout << "File does not exist\n";
    }
    printImage(file);
  } else if (extension == "mp4" || extension == "avi") {
    cv::VideoCapture cap(filename);
    if (!cap.isOpened()) {
      std::cout << "Failed to open video file.\n";
      exit(EXIT_FAILURE);
    }

    while (true) {
      cv::Mat frame;
      cap >> frame;

      if (frame.empty())
        break;

      // system("clear");
      printImage(frame);
      cv::waitKey(10);
    }
  } else {
    std::cout << "Invalid file extension.\n";
    exit(EXIT_FAILURE);
  }

  return 0;
}
