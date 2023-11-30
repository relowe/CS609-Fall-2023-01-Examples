{ pkgs }: {
	deps = [
   pkgs.unzip
		pkgs.python39Full
  pkgs.clang_12
		pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
    pkgs.ruby
    pkgs.valgrind
    pkgs.openjdk
	];
}