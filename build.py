import os
import pathlib
import subprocess

KERNEL_SECTOR_LENGTH = 50
SECTOR_SIZE = 0x200

def assemble_to_object(src_file, dst_file):
    subprocess.check_call(['nasm', '-felf32', '-o', dst_file, src_file])

def compile_to_object(src_file, dst_file):
    subprocess.check_call([
        'gcc',
        '-m32', '-nostdlib', '-Wall', '-Werror', '-Wno-main', '-std=c11', '-fno-asynchronous-unwind-tables', '-fno-pie',
        '-c', '-o', dst_file, src_file])

def link_to_binary(obj_files, dst_file):
    subprocess.check_call([
        'ld',
        '--oformat=binary', '-melf_i386', '-Ttext=0x7C00', '--omagic',
        '-o', dst_file] + obj_files)

def compile_c_files(c_files):
    obj_files = []

    for c_file in c_files:
        c_filename = str(c_file)
        obj_filename = c_filename.replace('.c', '.o')

        print('Compiling {}'.format(c_filename))
        compile_to_object(c_filename, obj_filename)

        obj_files.append(obj_filename)

    return obj_files

def build_os_binary():
    shell_obj_files = []

    print('Compiling Common...')
    common_obj_files = compile_c_files(pathlib.Path('.').glob('common/*.c'))

    print('Compiling Shell...')
    shell_obj_files += common_obj_files
    shell_obj_files += compile_c_files(pathlib.Path('.').glob('shell/*.c'))

    # link boot with the c files to create a binary
    print('Linking Shell...')
    link_to_binary(shell_obj_files, 'shell.bin')

    subprocess.check_call(['xxd', '--include', 'shell.bin', 'shell_bin.h'])

    kernel_obj_files = []

    # assemble boot
    print('Assembling boot...')
    assemble_to_object(str(pathlib.Path('kernel/boot.asm')), str(pathlib.Path('kernel/boot.o')))
    kernel_obj_files.append(str(pathlib.Path('kernel/boot.o')))

    print('Compiling Kernel...')
    kernel_obj_files += common_obj_files
    kernel_obj_files += compile_c_files(pathlib.Path('.').glob('kernel/*.c'))
    link_to_binary(kernel_obj_files, 'os.flp')

    # pad the binary to the necessary size
    print('Padding...')
    total_necessary_size = KERNEL_SECTOR_LENGTH * SECTOR_SIZE
    with open('os.flp', 'ab') as output_binary_file:
        # go to the end of the file
        output_binary_file.seek(0, os.SEEK_END)
        # get the size of the file
        current_size = output_binary_file.tell()
        # print the current size out of the total
        print('size: {} / {}'.format(current_size, total_necessary_size))
        # pad the file with zeros to reach the necessary size
        output_binary_file.truncate(total_necessary_size)

    # delete all .o files that were created
    for obj_file in pathlib.Path('.').glob('*/*.o'):
        pathlib.Path(obj_file).unlink()

    print('Done.')

def main():
    try:
        build_os_binary()
    except subprocess.CalledProcessError:
        print('There was an Error. Build aborted.')

if __name__ == '__main__':
    main()
