import os
import pathlib
import subprocess

KERNEL_SECTOR_LENGTH = 50

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

def build_os_binary():
    obj_files = []

    # assemble boot
    print('Assembling boot...')
    assemble_to_object('boot.asm', 'boot.o')
    obj_files.append('boot.o')

    # compile all c files in the current directory
    print('Compiling...')
    for c_file in pathlib.Path('.').glob('*.c'):
        c_filename = c_file.name
        obj_filename = c_filename.replace('.c', '.o')
        print('Compiling {}'.format(c_filename))
        compile_to_object(c_filename, obj_filename)
        obj_files.append(obj_filename)

    # link boot with the c files to create a binary
    print('Linking...')
    link_to_binary(obj_files, 'os.flp')

    # pad the binary to the necessary size
    print('Padding...')
    total_necessary_size = KERNEL_SECTOR_LENGTH * 0x200
    with open('os.flp', 'ab') as output_binary_file:
        output_binary_file.seek(0, os.SEEK_END)
        current_size = output_binary_file.tell()
        print('size: {} / {}'.format(current_size, total_necessary_size))
        output_binary_file.truncate(total_necessary_size)

    # delete all obj files that were created
    for obj_file in obj_files:
        pathlib.Path(obj_file).unlink()

    print('Done.')

def main():
    try:
        build_os_binary()
    except subprocess.CalledProcessError:
        print('There was an Error. Build aborted.')

if __name__ == '__main__':
    main()
