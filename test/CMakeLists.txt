itk_module_test()
set(ShapeBasedInterpolationTests
  ShapeBasedInterpolationImageDemo
)
CreateTestDriver(ShapeBasedInterpolation  "${ShapeBasedInterpolation-Test_LIBRARIES}" "${ShapeBasedInterpolationTests}")

itk_add_test(NAME ShapeBasedInterpolationImageDemo
      COMMAND ShapeBasedInterpolationTestDriver
    ShapeBasedInterpolationImageDemo
)

