# Fake Focus

First of all, this program is only an adaptation, unnoficial fork, of the amazing Universal Split Screen project that allows offline multiplayer with split-screen.
Fake Focus was created to help anyone who may want to keep its games running in the background without mute sound or input problems, whatever the reason. 
I hope this can help people as much as it helped me, and big tanks for Ilyaki and anyone who contributed to the creation of Universal Split Screen!!!

# UniversalSplitScreen
Split screen multiplayer for any game with multiple keyboards, mice and controllers.
https://universalsplitscreen.github.io/

### Compiling notes
Compile UniversalSplitScreen in x86.

Compile SourceEngineUnlocker in x86, and copy SourceEngineUnlocker.dll to the UniversalSplitScreen folder.

Compile InjectorLoader in x86 and x64. Copy IJx86.exe and IJx64.exe to the folder.

Compile HooksCPP in x86 and x64. Copy HooksCPP32.dll and HooksCPP64.dll to the folder.

Compile StartupHook in x86 and x64. Copy StartupHook32.dll and StartupHook64.dll to the folder.

The post-build options in the projects should automatically rename and copy as necessary.

You can use Batch build in Visual Studio to compile all the projects at once.
