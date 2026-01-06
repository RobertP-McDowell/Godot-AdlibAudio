# Adplug For Godot
A module meant to be compiled into the Godot Engine, to allow emulation of the OPL2 and OPL3 Adlib chips using Adplug!

# Working verisons
Godot: 4.4 Will not work for any Godot versions prior to 4.4.

Adplug: 2.3.3. static x64

Libbinio: 1.5. static x64

# Instructions

When compiling Libbinio and Adplug libraries, make sure they're made for x64, and are static libraries (*.lib, *.a).
Download the source code, place the adplug folder in your godot source folder, like this `godot/modules/adplug`.

Create a `lib/` folder in the adplug folder, place your compiled adplug and libbinio libraries within it.
Create an `include/` folder, libbinio headers go directly in it. Your adplug headers need to be in this subfolder `include/adplug/`.
Finally you can place the AudioStreamIcon.svg file into `godot/editor/icons`, So they show in the editor. And compile!

If you find that your Adlib file isn't being imported, you may need to comment in the extension in `resource_importer_adplug.cpp`.
You can edit the emulator and chip type in the import settings of your adlib file.

# WIP
The majority of emulators adplug supports, are not yet supported in this module. Adplugs primary emulator, and NukedOPL are the only to emulators. NukedOPL is most precise to the original OPL2 and OPL3 chips than any other adplug emulator from my understanding, therefore it is defualt.

Contributions are appreciated! You can request support be enabled for a specific emulator if you like, it shouldn't be hard to enable support for more.