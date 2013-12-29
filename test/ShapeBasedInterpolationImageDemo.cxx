/*===============================================================================================================
  Program:    Insight Segmentation & Registration Toolkit
  Language:   C++
  Date:       june 2012
  
  Authors belong to:
  - Ecole Polytechnique Fédérale de Lausanne STI-IEL-LTS5                  http://lts5www.epfl.ch
  - Université de Valenciennes et du Hainaut-Cambrésis - LAMIH, CNRS       http://www.univ-valenciennes.fr/LAMIH/
  Contact: christine.boydev@epfl.ch

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the implied 
  warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
  See the copyright notices for more information.
================================================================================================================*/

#include "itkInterBinaryShapeBasedInterpolationImageFilter.h"
#include "itkIntraBinaryShapeBasedInterpolationImageFilter.h"

#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>

#include <itkLinearInterpolateImageFunction.h>
#include <itkBSplineInterpolateImageFunction.h>
#include <itkNearestNeighborInterpolateImageFunction.h>


int main( int argc, char* argv[] )
{
  if( argc < 3 ) 
    { 
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << " inputImageFile outputImageFile (optional : type of interpolation)" << std::endl;
    return EXIT_FAILURE;
    }
  
  char* inputFile = argv[1];
  char* outputFile = argv[2];
  std::string interp; 
  bool answer = true;
  
  std::cout << "Are the delineated slices disjoint in your original image? Usage : 1 for true, 0 for false." << std::endl;
  std::cin >> answer;

  typedef unsigned char InputPixelType;
  const unsigned int Dimension = 3;
  
  typedef itk::Image< InputPixelType,  Dimension >                                       InputImageType;
  typedef itk::Image< InputPixelType,  Dimension >                                       OutputImageType;
  typedef itk::Image< double, Dimension >                                                IntermediateImageType;
  typedef itk::ImageFileReader< InputImageType >                                         ReaderType;
  typedef itk::ImageFileWriter< OutputImageType >                                        WriterType;
  typedef itk::InterpolateImageFunction< IntermediateImageType, double>                  InterpolatorType;
  typedef itk::NearestNeighborInterpolateImageFunction< IntermediateImageType, double >  NNInterpolatorType;
  typedef itk::LinearInterpolateImageFunction< IntermediateImageType, double >           LinearInterpolatorType;
  typedef itk::BSplineInterpolateImageFunction< IntermediateImageType, double >          BSplineInterpolatorType;
  
  std::cout << "Read image..." << std::endl;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( inputFile );

  InterpolatorType::Pointer interpolator;  
  if( argv[3]!='\0' )
  {
    interp = argv[3];
    if( interp == "nn" ) interpolator             =  NNInterpolatorType::New();
      else if( interp == "linear" ) interpolator  =  LinearInterpolatorType::New();
      else if( interp == "bspline" ) interpolator =  BSplineInterpolatorType::New();
      else std::cerr << "Error. I do not know interpolation. Choose among: nn, linear, bspline. By default : linear." << std::endl;
  }
  
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( outputFile );

  if( answer )
  {
    typedef itk::InterBinaryShapeBasedInterpolationImageFilter      FilterType;
    FilterType::Pointer filter = FilterType::New();
    filter->SetInput( reader->GetOutput() );
    filter->SetDelineationRatio( 3 );
    if( !(interp.empty()) ) filter->SetInterpolator( interpolator );
    writer->SetInput( filter->GetOutput() );
    try
    {
      writer->Update();
      std::cout << "Writing the image..." << std::endl;
    }
    catch( itk::ExceptionObject & excep )
    {
      std::cerr << "Exception caught !" << std::endl;
      std::cerr << excep << std::endl;
    }
  }
  else
  {
    typedef itk::IntraBinaryShapeBasedInterpolationImageFilter      FilterType;
    FilterType::Pointer filter = FilterType::New();
    filter->SetInput( reader->GetOutput() );
    filter->SetDelineationRatio( 3 );
    if( !(interp.empty()) ) filter->SetInterpolator( interpolator );
    writer->SetInput( filter->GetOutput() );
    try
    {
      writer->Update();
      std::cout << "Writing the image..." << std::endl;
    }
    catch( itk::ExceptionObject & excep )
    {
      std::cerr << "Exception caught !" << std::endl;
      std::cerr << excep << std::endl;
    }
  }
  
  return 0;  
}  // end main