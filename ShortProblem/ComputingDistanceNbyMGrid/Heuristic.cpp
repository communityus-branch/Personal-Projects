/*
*
*
* Author  : Tham Cheng Jiang
* Email   : tham_cj@outlook.com
*
* Date    : 6 Jan 2019
*
*/
#include <iostream>
#include <vector>
#define max(x,y) x>y?x:y

//! printing of table
void PrintTable(std::vector<std::vector<float>>& table, int Row, int Col)
{
  for (int i = Row - 1; i >= 0; i--)
  {
    for (int j = 0; j < Col; j++)
    {
      std::cout << table[i][j] << "\t\t";
    }
    std::cout << std::endl;
  }

}

//! To copy from the computation table
void CopyTable(std::vector<std::vector<float>>& from, std::vector<std::vector<float>>& to, int PosR, int PosC)
{
  size_t rowCopyLength = to.size();
  size_t colCopyLength = to[0].size();

  for (size_t itrRow = 0; itrRow < rowCopyLength; itrRow++)
  {
    size_t computeRow = rowCopyLength - PosR - 1;

    size_t computeCol = colCopyLength - PosC - 1;

    memcpy(&to[itrRow][0], &from[computeRow + itrRow][computeCol], colCopyLength * sizeof(float));

  }
}




int main()
{
  std::cout << "Input Table Size " << std::endl;
  std::cout << "Row m : ";

  unsigned M = 0;
  unsigned N = 0;

  while(M <= 0)
    std::cin >> M;

  std::cout << "Col n : ";

  while(N <= 0)
    std::cin >> N;

  std::cout << "Generating Table " << std::endl;

  std::vector<std::vector<float>> Table{ M, std::vector<float>(N,0) };
  std::vector<std::vector<float>> ComputationTable{ (M * 2) - 1, std::vector<float>((N * 2) - 1, 0) };

  int startM = M - 1;
  int startN = N - 1;

  unsigned maxValue = max(M, N);

  for (unsigned r = 1; r < maxValue; r++)
  {
    for (unsigned c = 0; c < maxValue; c++)
    {
      float value = sqrtf(static_cast<float>(r*r + c * c));
      if (r < M && c < N)
      {
        ComputationTable[startM + r][startN + c] = value;
        ComputationTable[startM - r][startN - c] = value;
      }

      if (r < N && c < M)
      {
        ComputationTable[startM - c][startN + r] = value;
        ComputationTable[startM + c][startN - r] = value;
      }

    }
  }

  std::cout << "Passing Value " << std::endl;
  CopyTable(ComputationTable, Table, 0, 0);

  std::cout << "Printing Table " << std::endl;
  PrintTable(Table, M, N);

  while (true)
  {
    std::cout << std::endl;
    std::cout << "-------------------------------------------------------------" << std::endl;
    std::cout << "To Exit - Pass in value < 0 for row || col" << std::endl;

    int posR = 0;
    int posC = 0;

    std::cout << "Enter position for row : ";
    do
    {
      std::cin >> posR;
    } while (posR >= static_cast<int>(M));

    if (posR < 0)
      break;

    std::cout << "Enter position for col : ";
    do
    {
      std::cin >> posC;
    } while (posC >= static_cast<int>(N));

    if (posC < 0)
      break;

    std::cout << std::endl;
    CopyTable(ComputationTable, Table, posR, posC);
    PrintTable(Table, M, N);
  }

}
