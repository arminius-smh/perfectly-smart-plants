Setting Up Home Assistant
===

# VM

## Install qemu
We use qemu. It might be necessary to install it. Follow these [Direction](https://itsfoss.com/qemu-ubuntu/)

But a quick ***overview***:
1. Check if virtualisation possible
2. Install "qemu"
3. Add user to groups
4. Start service

## Create Virtual Machine

Follow these [Instructions](https://www.home-assistant.io/installation/alternative/)

1. Download Image and uncompress
2. Follow KVM(virt-manager) instuction with some differences
    - for network selection
        - choose *bridge* and type in "virbr0"
        - install "qemu-system-common" if not installed
        - enable ipv4 forwarding
            - in "/etc/sysctl.conf" uncomment the line "net.ipv4.ip_forward = 1"
        - 
    - bevore adding new hardware channel, check if one already exists


# HA Setup

1. Create new user
2. Set Location

