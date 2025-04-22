{
  description = "Nix POOSE flake";

  inputs = {
    flake-parts.url = "github:hercules-ci/flake-parts";

    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";

    treefmt-nix = {
      url = "github:numtide/treefmt-nix";
      inputs.nixpkgs.follows = "nixpkgs";
    };
  };

  outputs =
    inputs@{ flake-parts, ... }:
    flake-parts.lib.mkFlake { inherit inputs; } {
      systems = [
        "aarch64-darwin"
        "aarch64-linux"
        "x86_64-darwin"
        "x86_64-linux"
      ];

      imports = [ inputs.treefmt-nix.flakeModule ];

      perSystem =
        { pkgs, ... }:
        {
          treefmt = ./treefmt.nix;

          devShells.default = pkgs.mkShell {
            buildInputs = [
              pkgs.qt6.qtbase
              # There is also pkgs.qt6.full
            ];

            nativeBuildInputs = [ pkgs.qt6.wrapQtAppsHook ];

            packages = with pkgs; [
              nil

              meteor-git
              just

              git
              meld # recommended by uni

              stdenv.cc.cc.lib # libstdc++-dev
              clang
              cmake

              (python313.withPackages (
                subpkgs: with subpkgs; [
                  pybind11
                  pyside6
                  fastapi
                ]
              ))
            ];
          };
        };
    };
}
