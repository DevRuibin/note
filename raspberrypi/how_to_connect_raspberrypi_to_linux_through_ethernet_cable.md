# How to connect the Raspberry Pi to Linux through ethernet cable

To accelerate the speed of communication between the Raspberry Pi and the Linux computer, we can connect them through an ethernet cable. This is a very simple process, but it requires some configuration.

1. Connect the Raspberry Pi and the Linux computer through an ethernet cable.
2. On Linux
   1. Open the Network Manager.
   2. Edit your Ethernet connection.
   3. Go to the IPv4 tab.
   4. Change the Method to "Mannual".
   5. Click on "Add" under the "Addresses" section.
      * Address: "198.168.2.1"
      * Netmask: "24"
      * Gateway: Leave it blank
   6. Turn off the "Automatic" toggle and leave the DNS field blank.
   7. Click on "Apply".
   8. Disconnect and reconnect the ethernet cable or toggle the connection off and on for the changes to take effect.
3. On the Raspberry Pi
   1. Open the terminal.
   2. Edit the dhcpcd configuration file: `sudo vim /etc/dhcpcd.conf`
   3. Add the following lines to the end of the file:
      
      ```bash
      interface eth0
      static ip_address=192.168.2.2/24
      ```
   4. Save and exit the file.
   5. Restart the dhcpcd service: `sudo service dhcpcd restart`

Now you can connect to the Raspberry Pi through SSH using the IP address "192.168.2.2". 