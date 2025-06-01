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
    cpptrace
    fmt
    gtest
  ];

  nativeBuildInputs = [
    cmake
  ];

  dontStrip = true;
  cmakeBuildType = "RelWithDebInfo";

  doCheck = false;
}
