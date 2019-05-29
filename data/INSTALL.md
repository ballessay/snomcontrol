# Arch

copy snomcontrol.desktop to ~/.local/share/applications

xdg-settings set default-url-scheme-handler tel snomcontrol.desktop
xdg-settings get default-url-scheme-handler tel


## firefox

See: [http://kb.mozillazine.org/Register_protocol]()

firefox (change tel to sip, callto...):
about:config
Add new boolean
network.protocol-handler.expose.tel value: false

# ubuntu ex
gconftool-2 -s /desktop/gnome/url-handlers/tel/command '/home/cballes/bin/snomcontrol %s' --type String
gconftool-2 -s /desktop/gnome/url-handlers/tel/enabled --type Boolean true

# Windows 10

Double click snomcontrol.reg

win + r or in explorer.exe adressbar: control /name Microsoft.DefaultPrograms /page pageDefaultProgram => Default Apps by Protocol
