/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkNewMinimumMaximumImageCalculatorTest.cxx,v $
  Language:  C++
  Date:      $Date: 2007-08-10 14:34:02 $
  Version:   $Revision: 1.3 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include <fstream>
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkPNGImageIOFactory.h"
#include "itkTextOutput.h"
#include "itkImageRegionIterator.h"
#include "itkNumericTraits.h"
#include "itkFilterWatcher.h"
#include "itkNewMinimumMaximumImageCalculator.h"

// Global typedefs
typedef unsigned char PixelType;
typedef itk::Image<PixelType, 2> ImageType;

// Global variables
ImageType::Pointer image;
std::vector<ImageType::IndexType> whiteIndices;
std::vector<ImageType::IndexType> bgrayIndices;
std::vector<ImageType::IndexType> dgrayIndices;

// Function for creating demo image
void CreateDemoImage(std::string path);

int main(int ac, char* av[])
{
  // Comment the following if you want to use the itk text output window
  itk::OutputWindow::SetInstance(itk::TextOutput::New());
  
  // Set path to write output image  
  std::string path;
  if(ac < 2)
    path = "images/";
  else
    path = av[1];

  // Create the demo image
  CreateDemoImage(path);
  
  // Example usage
  typedef itk::NewMinimumMaximumImageCalculator<ImageType> MinMaxCalcType;
  MinMaxCalcType::Pointer minMaxCalc = MinMaxCalcType::New();
  minMaxCalc->SetImage(image);  
  minMaxCalc->Compute(0, 255); // exclude 0 and 255 from computation
  
  // Failure flag
  bool testFailureFlag = 0;
  if(minMaxCalc->GetMaximum() != 164) // maximum should be 164
    {
	std::cerr << "Error in Compute(PixelType excludeMin, PixelType excludeMax)" << std::endl;
    testFailureFlag = 1;
    }
  if(minMaxCalc->GetMinimum() != 96) // minimum should be 96
    {
	std::cerr << "Error in Compute(PixelType excludeMin, PixelType excludeMax)" << std::endl;
    testFailureFlag = 1;
    }
   
  // GetIndicesOfMaximum() should match number of indices stored in bgrayIndices - dgrayIndices
  if(minMaxCalc->GetIndicesOfMaximum().size() != (bgrayIndices.size() - dgrayIndices.size()))
    {
	std::cerr << "Error in GetIndicesOfMaximum()" << std::endl;
	std::cerr << "minMaxCalc->GetIndicesOfMaximum().size(): " << minMaxCalc->GetIndicesOfMaximum().size() << std::endl;
	std::cerr << "bgrayIndices.size() - dgrayIndices.size(): " << bgrayIndices.size() - dgrayIndices.size() << std::endl;
	testFailureFlag = 1;
	}
  
  minMaxCalc->ComputeMaximum(255); // exclude 255 from maximum computation
  if(minMaxCalc->GetMaximum() != 164) // maximum should be 164
    {
    std::cerr << "Error in ComputeMaximum(PixelType excludeMax)" << std::endl;
    testFailureFlag = 1;
    }
  // GetIndicesOfMaximum() should match number of indices stored in bgrayIndices - dgrayIndices
  if(minMaxCalc->GetIndicesOfMaximum().size() != (bgrayIndices.size() - dgrayIndices.size()))
    {
	std::cerr << "Error in GetIndicesOfMaximum()" << std::endl;
	std::cerr << "minMaxCalc->GetIndicesOfMaximum().size(): " << minMaxCalc->GetIndicesOfMaximum().size() << std::endl;
	std::cerr << "bgrayIndices.size() - dgrayIndices.size(): " << bgrayIndices.size() - dgrayIndices.size() << std::endl;
	testFailureFlag = 1;
	}
    
  minMaxCalc->ComputeMinimum(0); // exclude 0 from minimum computation
  if(minMaxCalc->GetMinimum() != 96) // minimum should be 96
    {
    std::cerr << "Error in ComputeMinimum(PixelType excludeMin)" << std::endl;
    testFailureFlag = 1;
    }
  // GetIndicesOfMinimum() should match number of indices stored in dgrayIndices
  if(minMaxCalc->GetIndicesOfMinimum().size() != dgrayIndices.size())
    {
	std::cerr << "Error in GetIndicesOfMinimum()" << std::endl;
	std::cerr << "minMaxCalc->GetIndicesOfMinimum().size(): " << minMaxCalc->GetIndicesOfMinimum().size() << std::endl;
	std::cerr << "dgrayIndices.size(): " << dgrayIndices.size() << std::endl;
	testFailureFlag = 1;
	}
  
  if(testFailureFlag == 0)
    {
	std::cerr << "Test passed!" << std::endl;  
    return EXIT_SUCCESS;
    }
  else
    {
	std::cerr << "Test failed!" << std::endl;
    return EXIT_FAILURE;
    }
}

void CreateDemoImage(std::string path)
{
  // Create a 200 x 200 image filled with 0 value pixels.
  image = ImageType::New();
  ImageType::RegionType region;
  ImageType::RegionType::IndexType start;
  start[0] = 0;
  start[1] = 0;
  region.SetIndex(start);
  ImageType::RegionType::SizeType size;
  size[0] = 200;
  size[1] = 200;
  region.SetSize(size);
  image->SetLargestPossibleRegion(region);
  image->SetBufferedRegion(region);
  image->SetRequestedRegion(region);
  double origin[2];
  origin[0] = 0;
  origin[1] = 0; 
  image->SetOrigin(origin);  
  ImageType::SpacingType spacing;
  spacing[0] = 1;
  spacing[1] = 1;
  image->SetSpacing(spacing);
  image->Allocate();
  image->FillBuffer(0);
  
  // Draw a 99 x 99 white (255) box in the center of the image
  ImageType::IndexType index;
  whiteIndices.clear();
  unsigned int cx = 99;
  unsigned int cy = 99;
  for(int j = -49; j <= 49; j++)
    {
	index[1] = j + cy;
    for(int i = -49; i <= 49; i++)
      {
      index[0] = i + cx;
      image->SetPixel(index, 255);
      whiteIndices.push_back(index);
      }
	}
  
  // Draw a 49 x 49 bright gray (164) box in the center of the image
  bgrayIndices.clear();
  for(int j = -24; j <= 24; j++)
    {
	index[1] = j + cy;
    for(int i = -24; i <= 24; i++)
      {
      index[0] = i + cx;
      image->SetPixel(index, 164);
      bgrayIndices.push_back(index);
      }
	}

  // Draw a 25 x 25 dark gray (96) box in the center of the image
  dgrayIndices.clear();
  for(int j = -12; j <= 12; j++)
    {
	index[1] = j + cy;
    for(int i = -12; i <= 12; i++)
      {
      index[0] = i + cx;
      image->SetPixel(index, 96);
      dgrayIndices.push_back(index);
      }
    }
    
  // Write image out
  itk::ImageFileWriter<ImageType>::Pointer writer;
  writer = itk::ImageFileWriter<ImageType>::New();
  writer->SetInput(image);
  writer->SetFileName(path + std::string("NewMinimumMaximumImageCalculatorTest_output.png"));
  writer->Update();
}
