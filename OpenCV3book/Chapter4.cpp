#include <opencv2/opencv.hpp>
#include <cstdlib> // For rand()
#include <iostream>
#include <conio.h>

using namespace std;

#pragma region firstEx

#define KEY_ENTER 13
#define KEY_ESC 27
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

uint g_curRow = 0;
uint g_curCol = 0;
// We know the final type - using template to avoid at<>()
cv::Mat_<uchar> g_matFirstInput = cv::Mat::zeros(20, 10, CV_8U);

//1. Create a 500 x 500 single channel uchar image with every pixel equal to zero.
//a.Create an ASCII numeric typewriter where you can type numbers into your
//computer and have the number show up in a 20 - pixel - high by 10 - pixel - wide
//block.As you type, the numbers will display from left to right
//b.Allow for arrow keys to edit each number.
//c.Create a key that will convert the resulting image into a color image, each
//number taking on a different color.

/// @brief input mode, allowing changing items of matrix
void inputMode()
{
  int curVal = g_matFirstInput(g_curRow, g_curCol);
  while (true)
  {
    int input = -1;
    cout << "[Input Mode] Write number in range of [0, 255]" << endl;
    cout << "[Input Mode] Current number is: " << curVal <<endl;
    cin >> input;

    if (input >= 0 && input <= 255)
    {
      g_matFirstInput(g_curRow, g_curCol) = static_cast<uchar>(input);
      return;
    }
  }
}

/// @brief print matrix
void paintMatrix()
{
  for (int i = 0; i < g_matFirstInput.rows; ++i)
  {
    for (int z = 0; z < g_matFirstInput.cols; ++z)
    {
      cout << static_cast<int>(g_matFirstInput(i, z));

      if (i == g_curRow && z == g_curCol)
        cout << "*";

      cout << " ";
    }
    cout << endl;
  }
}

/// @brief Navigation in the matrix
void navigationMode()
{
  while (true)
  {
    paintMatrix();

    int inputKey;
    cout << "Cuttent position is " << g_curRow << ", " << g_curCol << endl;
    cout << "[Navigation] Press <Enter> to write number, <Arrows> to navigate, <Esc> to proceed to image generation" << endl;
    inputKey = _getch();
    switch (inputKey)
    {
    case KEY_ENTER:
      inputMode();
      break;

    case KEY_ESC:
      return;

    case KEY_LEFT:
      if (g_curCol > 0)
        --g_curCol;
      break;

    case KEY_RIGHT:
      if (g_curCol < 9)
        ++g_curCol;
      break;

    case KEY_UP:
      if (g_curRow > 0)
        --g_curRow;
      break;

    case KEY_DOWN:
      if (g_curRow < 19)
        ++g_curRow;
      break;

    default:
      break;
    }
  }
}

void firstEx()
{
  // Making own Matrix process
  navigationMode();

  // Image 500x500 filled with 0 uchar 1 channel (grayscale)
  cv::Mat matResizedGray;
  cv::resize(g_matFirstInput, matResizedGray, cv::Size(500, 500), 0, 0, cv::INTER_LINEAR);

  // Now 3 channel (BGR)
  cv::Mat matResizedColor;
  cv::cvtColor(matResizedGray, matResizedColor, cv::COLOR_GRAY2BGR);

  // Show output Grayscale 1 channel
  cv::imshow("Grayscale", matResizedGray);
  // Show output Grayscale 3 channel
  cv::imshow("Color", matResizedColor);
  cv::waitKey(0);
}
// firstEx region
#pragma endregion

int main(int argc, char* argv[]) 
{
  firstEx();
  return 0;
}