#!/usr/bin/python
import os
import subprocess
import pathlib

class colors:
    OKGREEN = '\033[92m'
    ENDC = '\033[0m'

def percent(part, whole):
    return round(100 * (float(part) / float(whole)))

class project:
    def __init__(self, name, source_dir, include_dirs=[], compiler="g++", language="c", libs=[], binary_dir="bin"):
        self.source_dir = source_dir
        self.include_dirs = include_dirs
        self.compiler = compiler
        self.project_name = name
        self.exec_name = name
        self.extensions = []
        self.pkg_config_string = ""
        self.object_files = []
        self.binary_dir = binary_dir


        match str.lower(language):
            case "c":
                self.extensions = ["c"]

            case "cpp":
                self.extensions = ["cc", "cxx", "cpp"]

            case _:
                print(f"[LOG] Unrecognised language input \"{language}\". valid inputs are: c, cpp")


        if libs != []:
            self.pkg_config_string = subprocess.getoutput(f"pkg-config --libs {" ".join(libs)}")

    def get_files(self, _d):
        files = []
        for dir, _, filenames in os.walk(_d):
            for filename in filenames:
                if list(filter(filename.endswith, self.extensions)) != []:
                    files.append(os.path.join(dir, filename))

        return files

    def compile(self, compile_flags="-O0"):
        source_files = self.get_files(self.source_dir)
        if self.binary_dir != "" and not os.path.exists(self.binary_dir):
            os.mkdir(self.binary_dir)

        for srcfile in source_files:
            current = source_files.index(srcfile)+1
            file_ext = pathlib.Path(srcfile).suffix
            output_file = os.path.join(self.binary_dir, os.path.basename(srcfile).replace(file_ext, ".o"))
            include_flags = " ".join([f"-I{inc}" for inc in self.include_dirs])
            compile_command = f"{self.compiler} {compile_flags} -o {output_file} -c {srcfile} {include_flags}"

            print(f"{colors.OKGREEN}[{percent(current, len(source_files))}%] Compiling{colors.ENDC}: {compile_command}")
            subprocess.check_call(compile_command, shell=True)
            self.object_files.append(output_file)


    def link_files(self, lto=False, lto_mode="", ld="ld", ld_flags="-Wl,-O1,--as-needed", compiler_flags="-O0"):
        build_to = f"{self.binary_dir}/" if self.binary_dir != "" else ""
        lto_flag = ""
        if lto != False:
            lto_flag = "-flto"
            if len(lto_mode) > 0:
                lto_flag += f"={lto_mode}"

        link_command = f"{self.compiler} {compiler_flags} {ld_flags} -fuse-ld={ld} {lto_flag} {" ".join(self.object_files)} -o {build_to}{self.exec_name} {self.pkg_config_string}"
        print(f"Linking: {link_command}")
        subprocess.check_call(link_command, shell=True)

    def delete_obj_files(self):
        for obj in self.object_files:
            subprocess.check_call(f"rm {obj}", shell=True)

prj = project("build", "src/", compiler="clang++", language="cpp", binary_dir="")
prj.compile("-O2 -pipe")
prj.link_files(ld_flags="-Wl,-O2,--as-needed,--sort-common", compiler_flags="-O2 -pipe", lto=False)
prj.delete_obj_files()
