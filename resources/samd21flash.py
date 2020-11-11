import os
import argparse

if __name__ == "__main__":

    parser = argparse.ArgumentParser()
    parser.add_argument("-port")
    parser.add_argument("-programmer")
    parser.add_argument("-binary")

    args = parser.parse_args()
    port_norm = args.port
    port_bootloader = f"{port_norm[0:3]}{int(port_norm[-1])+1}"

    print("Issuing command to bootloader with 1200 baud")
    os.system(f'cmd /k "mode {port_bootloader}:1200,n,8,1,p"')
    print("Complete.\nFlashing device.")
    os.system(f'cmd /k "{args.programmer}" --port={port_norm} -i -e -w -v -b {args.binary} -R')