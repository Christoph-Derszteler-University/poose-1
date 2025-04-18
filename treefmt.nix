{
  programs = {
    # Nix
    deadnix.enable = true;
    statix.enable = true;
    nixfmt = {
      enable = true;
      strict = true;
    };

    # C/C++
    clang-format.enable = true;
    cmake-format.enable = true;

    # Python
    ruff-check.enable = true;
    ruff-format.enable = true;

    # Multiple
    prettier.enable = true;
  };
}
