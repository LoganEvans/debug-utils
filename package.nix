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
    "dev"
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

  doCheck = false;
}
