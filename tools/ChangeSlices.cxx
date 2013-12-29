/* This code modifies all the pixels that belong to certain slices (equally spaced) in an image. It sets their value to zero  (the background). 
 * In our test, this code was given a binary image (the initial cone or the initial prostate image) so that it could give a binary image wherein 
 * some regularly spaced slices are empty (made of pixels at zero).
 * */


#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkImage.h>
#include <itkImageSliceIteratorWithIndex.h>

int main( int argc, char* argv[] )
{ 
  char* inputFile = argv[1];
  char* outputFile = argv[2];
  
  typedef itk::Image< unsigned char,  3 >                                 InputImageType;
  typedef itk::Image< unsigned char,  3 >                                 OutputImageType;
  typedef itk::ImageFileReader< InputImageType >                          ReaderType;
  typedef itk::ImageFileWriter< OutputImageType >                         WriterType;
  
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( inputFile );
  reader->Update();
  
  InputImageType::Pointer inputImage = InputImageType::New();
  inputImage=reader->GetOutput();
  InputImageType::RegionType inputRegion = inputImage->GetLargestPossibleRegion();

  typedef itk::ImageSliceIteratorWithIndex< InputImageType >   SliceItType;
  SliceItType sliceIt( inputImage, inputRegion );
  sliceIt.SetFirstDirection(0);
  sliceIt.SetSecondDirection(1);
  sliceIt.GoToBegin(); 
    
  InputImageType::IndexType inputStart;   
  while( !sliceIt.IsAtEnd() )
  {
    inputStart = sliceIt.GetIndex();
    if ( (inputStart[2] % 2) == 0 ) std::cout << "inputStart" << inputStart << std::endl;
    while( !sliceIt.IsAtEndOfSlice() )
    {
      while( !sliceIt.IsAtEndOfLine() )
      {
	if ( !(inputStart[2] % 2) == 0 ) sliceIt.Set(0);
	//if ( !(inputStart[2] % 3) == 0 ) sliceIt.Set(0);
        ++sliceIt;
      }
      sliceIt.NextLine();
    }
    sliceIt.NextSlice();
  }
  
  WriterType::Pointer writer = WriterType::New();
  writer->SetInput( inputImage  );
  writer->SetFileName( outputFile );
  writer->Update();
 return 0;  
}  // end main