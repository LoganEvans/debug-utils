{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs";
    flake-utils.url = "github:numtide/flake-utils";

    treefmt-nix.url = "github:numtide/treefmt-nix";
    treefmt-nix.inputs.nixpkgs.follows = "nixpkgs";
  };

  outputs =
    {
      self,
      nixpkgs,
      flake-utils,
      treefmt-nix,
    }:
    flake-utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = import nixpkgs {
          inherit system;
          config.allowUnfree = true;
        };

        debug-utils-drv = pkgs.callPackage ./package.nix {
          src = self;
        };

        treefmtEval = treefmt-nix.lib.evalModule pkgs ./treefmt.nix;
      in
      {
        packages = rec {
          debug-utils = debug-utils-drv;

          test = debug-utils-drv.overrideAttrs (attrs: {
            cmakeBuildType = "Debug";
            doCheck = true;
          });

          default = debug-utils-drv;
        };

        devShells.default = debug-utils-drv.overrideAttrs (old-attrs: {
          cmakeBuildType = "Debug";
          doCheck = true;
        });

        formatter = (pkgs: treefmtEval.config.build.wrapper) { };
      }
    );
}
