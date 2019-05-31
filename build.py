import os
import pathlib
import subprocess

KERNEL_SECTOR_LENGTH = 50

SECTOR_SIZE = 0x200
OUTPUT_FILENAME = 'os.flp'

def assemble_to_object(src_file, dst_file):
    subprocess.check_call(['nasm', '-felf32', '-o', dst_file, src_file])

def compile_to_object(src_file, dst_file):
    subprocess.check_call([
        'gcc',
        '-m32', '-nostdlib', '-Wall', '-Werror', '-Wno-main', '-std=c11', '-fno-asynchronous-unwind-tables',
        '-c', '-o', dst_file, src_file])

def link_to_binary(obj_files, dst_file):
    subprocess.check_call([
        'ld',
        '--oformat=binary', '-melf_i386', '-Ttext=0x7C00', '--omagic',
        '-o', dst_file] + obj_files)

def pad_binary(filename, target_size):
    with open(filename, 'ab') as binary_file:

            # go to the end of the file
            binary_file.seek(0, os.SEEK_END)

            # get the size of the file
            previous_size = binary_file.tell()

            # pad the file with zeros to reach the necessary size
            binary_file.truncate(target_size)

    # return the size before padding
    return previous_size

def delete_files(filename_list):
    for filename in filename_list:
        # delete the file
        pathlib.Path(filename).unlink()

def glob(glob_expression):
    return [matched_file.name for matched_file in pathlib.Path('.').glob(glob_expression)]

def replace_extension(filename, from_extension, to_extension):
    the_file = pathlib.Path(filename)
    assert the_file.suffix == from_extension
    new_filename = the_file.with_suffix(to_extension).name
    return new_filename

def build_os_binary():
    obj_files = []

    try:
        # assemble boot
        print('1. Assembling boot...')
        assemble_to_object('boot.asm', 'boot.o')
        obj_files.append('boot.o')

        # compile all c files in the current directory
        print('2. Compiling...')
        c_files_to_compile = glob('*.c')
        for i, c_filename in enumerate(c_files_to_compile):
            obj_filename = replace_extension(c_filename, '.c', '.o')

            print('Compiling {}... ({} / {})'.format(c_filename, i + 1, len(c_files_to_compile)))
            compile_to_object(c_filename, obj_filename)

            obj_files.append(obj_filename)

        # link boot with the c files to create a binary
        print('3. Linking...')
        link_to_binary(obj_files, OUTPUT_FILENAME)

    finally:
        # delete all .o files that were created, even if there was an error
        delete_files(obj_files)

    # pad the binary to the necessary size
    print('4. Padding...')
    total_necessary_size = KERNEL_SECTOR_LENGTH * SECTOR_SIZE
    previous_size = pad_binary(OUTPUT_FILENAME, total_necessary_size)
    # print the size out of the total
    print('Size: {} / {}'.format(previous_size, total_necessary_size))

    print('5. Done.')

def main():
    try:
        build_os_binary()
    except subprocess.CalledProcessError:
        print('There was an Error in one of the steps. Build aborted.')

if __name__ == '__main__':
    main()
