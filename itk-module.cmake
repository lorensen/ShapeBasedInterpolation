set(DOCUMENTATION "This module contains a classes to perform shape based interpolation of binary images." )

itk_module( ShapeBasedInterpolation
  DEPENDS
    ITKCommon
    ITKDistanceMap
    ITKImageFunction
    ITKImageGrid
    ITKTransform
# Image IO Modules
    ITKIOJPEG
    ITKIOGDCM
    ITKIOBMP
    ITKIOLSM
    ITKIOPNG
    ITKIOTIFF
    ITKIOVTK
    ITKIOStimulate
    ITKIOBioRad
    ITKIOMeta
    ITKIONIFTI
    ITKIONRRD
    ITKIOGIPL
# Transform IO Modules
    ITKIOTransformMatlab
    ITKIOTransformHDF5
    ITKIOTransformInsightLegacy
  TEST_DEPENDS
    ITKTestKernel
  EXCLUDE_FROM_DEFAULT
  DESCRIPTION
    "${DOCUMENTATION}"
)

