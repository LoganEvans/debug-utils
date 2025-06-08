{
  clangStdenv,
  cmake,
  cpptrace,
  fmt,
  gtest,
  src,
}:
let
in
clangStdenv.mkDerivation {
  inherit src;
  name = "debug-utils";

  outputs = [
    "out"
  ];

  buildInputs = [
    gtest
  ];

  propagatedBuildInputs = [
    cpptrace
    fmt
  ];

  nativeBuildInputs = [
    cmake
  ];

  dontStrip = true;
  cmakeBuildType = "RelWithDebInfo";
  separateDebugInfo = true;

  doCheck = false;
}
