# Deprecated
I'm done using Godot and done with this project by extension, I'll leave it up in case anyone is getting some use out of it, however I made this when I was first learning C++ and buildsystems in general, so there are a few glaring issues worth noting.

This project does not have instructions for compilation with dynamically linked adplug libraries, which would allow you too distribute your project without it required to be open source due to Adplugs LGPL license.

The majority of emulators adplug supports, are not supported in this module. Adplugs primary emulator, and NukedOPL are the only emulators available. NukedOPL is most precise to the original OPL2 and OPL3 chips than any other adplug emulator from my understanding, therefore it is the default.

# Adplug For Godot
A module meant to be compiled into the Godot Engine, to allow emulation of the OPL2 and OPL3 Adlib chips using Adplug!

# Tested verisons
Godot: 4.4 Will not work for any Godot versions prior to 4.4.

Adplug: 2.3.3 static x64, Libbinio: 1.5 static x64

As stated above you cannot distribute a project with static libraries unless it's open source, however that is all that's been tested.

# Compiling
When compiling Libbinio and Adplug libraries, make sure they're made for x64, and are static libraries (*.lib, *.a).
Download the source code, place the adplug folder in your godot source folder, like this `godot/modules/adplug`.

Create a `lib/` folder in the adplug folder, place your compiled adplug and libbinio libraries within it.
Create an `include/` folder, libbinio headers go directly in it. Your adplug headers need to be in this subfolder `include/adplug/`.
Finally you can place the AudioStreamIcon.svg file into `godot/editor/icons`, So they show in the editor. And compile!

If you find that your Adlib file isn't being imported, you may need to comment in the files extension in `resource_importer_adplug.cpp`.
You can edit the emulator and chip type in the import settings of your adlib file.
