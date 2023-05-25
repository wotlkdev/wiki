---
layout: default
title: Server Debugging (Windows)
nav_order: 5
---

# Server Debugging (Windows)

Debugging is a powerful method to figure out exactly what a running program is doing while it does it.

A _debugger_ is a type of program used to take control of another program in order to see what it is doing and what data is in its memory. In WoW development, the debugger we use is usually _Visual Studio_, and the executable we debug is usually the _worldserver_, but any program can be attached to a debugger.

WoW servers are written in C++, and for a debugger to be useful in practice it is generally necessary to have a basic understanding of C++. Beginners might still find some value in skimming over this section to get an idea of what core developers actually mean when they talk about "debugging the server".

## Compiling for Debugging

In order for our debugger to do anything useful, we need to compile the worldserver in **Debug** mode. This makes the server significantly slower and should never be used on a live production server.

### Repacks

If you are using a repack, you cannot recompile the program in debug mode. You need to build your core from source for that..

### TrinityCore/AzerothCore

Building in Debug mode is as easy as opening the project in Visual Studio and changing the build type, then recompile. Your new core folder should be built into the same base folder as your previous builds, but into `Debug` instead of `RelWithDebInfo` or `Release`. You can copy over your map/dbc/.conf/mysql/libcrypto files from the previous build.

<img class="mi ili" src="https://i.imgur.com/wXu09Jo.png">

### TSWoW

Building the core in debug mode can be done from the [interactive build prompt](https://tswow.github.io/tswow-wiki/installation/compiling) by typing in `build trinitycore-debug`.

<img class="img_prompt" src="https://i.imgur.com/wCGLMFj.png">

<img class="img_prompt" src="https://i.imgur.com/5bUBo7f.png">

Then, to make your tswow installation use the debug binary, change the `Default.BuildType` to `Debug` inside `tswow-install/node.conf`. 

<img class="img_prompt" src="https://i.imgur.com/6LJpAPN.png">

Finally, if using C++ livescripts, make sure to rebuild them once from the main script (`build scripts`) and then start the server.

<img class="img_prompt" src="https://i.imgur.com/ySR1IDo.png">

<img class="img_prompt" src="https://i.imgur.com/oLniYPc.png">

## Configuring for Debugging

Normally, modern cores have a "Freeze Detector" built in, that will kick in and crash the server if it gets stuck for more than 60 seconds.

When debugging, we might cause the server to stop for longer than that on purpose, so it's best to disable this feature in our configuration files before we start.

For most modern cores, this is done by setting the `MaxCoreStuckTime` setting to `0` in our `worldserver.conf` (make sure you to this to the `worldserver.conf` in the **Debug** folder!)

<img class="img_prompt" src="https://i.imgur.com/nmrAYX4.png">

## Attaching the Debugger

First, we start our debug version of the worldserver the way you usually do for your core. Here, we should double-check that we are indeed running the Debug build of  our core:

<img class="mi ili" src="https://i.imgur.com/UqOOZkX.png">

Then, we should open the Visual Studio project for the core.

<img class="mi ili" src="https://i.imgur.com/p4MGR0C.png">

Then, we navigate to the "Debug" menu window and select `Attach to Process`.

<img class="mi ili" src="https://i.imgur.com/xCHMMcX.png">

This should bring up a dialog like below, where we can search for `worldserver` to easily find our process, and then click "Attach" to attach the debugger.

<img class="mi ili" src="https://i.imgur.com/cnQMPOU.png">

Once attached, the layout of our Visual Studio Window should change slightly to show the following information:

1. How much memory the process is currently using

2. The "Call Stack" window (it should be empty)

3. If the call stack window is not showing, you may need to click this little button

<img class="mi ili" src="https://i.imgur.com/PmRTi8b.png">

## Breakpoints

So, we've attached a debugger to a process and ... nothing happened?

By default, the debugger doesn't do anything to the process it attaches to, and will allow it to continue executing normally just like before. To actually make the program stop, we need to use **breakpoints**.

A breakpoint is a little toggle we can apply to individual lines of code where we want the debugger to stop the program from executing. In Visual Studio, we can easily add a breakpoint by clicking in the sidebar to the left of a line in our code:

<img class="mi ili" src="https://i.imgur.com/Cdz3Pih.png">

When we click it, a little red circle should appear. We have now instructed the debugger to stop the program from executing when it reaches this point. The line we've stopped it at now happens to be the internal code that is fired when a player gains a level.

Let's hop onto the game and try to level up and see if we can get the debugger to activate.

<img class="mi ili" src="https://i.imgur.com/0FyOWNN.png">

If everything went right, nothing should happen in the game when you type this command, as if the server had crashed. Instead, the Visual Studio window might pop up (if not, you may need to bring it up manually), and some things should've visible changed:

1. Our breakpoint now shows a little arrow inside of it. This means that the debugger is now stuck on this point of the program, which is why the game no longer responds.

2. Our call stack window should contain multiple lines of text. This is an outline of the hierarchy of function calls to where we stopped the program, this is the same kind of call stacks that we discussed in the previous [Crashlogs](./crashlogs) tutorial.

<img class="mi ili" src="https://i.imgur.com/KTTZNd5.png">

### Breakpoint Controls

Just stopping the executable isn't too useful on its own, what we want is a way to carefully control control the programs execution from our current position to see exactly how a computation takes places. The basic controls at our disposal are:

1. Continue - This resumes the execution of the program back to normal until another breakpoint is hit. This is what we press when we're done debugging for now or want to jump forward to another breakpoint.

2. Step Into - If we currently have a line with a function call selected, will call that function and move the debugger into it.

3. Step over - Executes the current line and moves to the next, without 'stepping in' to any function calls that we pass.

4. Step out - Resumes execution and stops the debugger again once we've exited the current function.

<img class="mi ili" src="https://i.imgur.com/KoRh12U.png">

Let's step press "Step over" (3) and move the cursor into the function body:

<img class="mi ili" src="https://i.imgur.com/JKsX8IA.png">

### Inspecting Variables

When we have suspended execution of a program with the debugger, we can inspect the current state of the program by hovering local variables, global variables and class fields to see their values.

Here, we inspect the "level" argument that the GiveLevel function accepted. Since we started at level 1 and leveled up to level 2, we can see that the argument to this function is "2".

<img class="mi ili" src="https://i.imgur.com/CK3dN2f.png">

We can also inspect other variables in the current program, like "oldLevel". As we do, we might get a strange surprise:

<img class="mi ili" src="https://i.imgur.com/OMi2Jpp.png">

How come the program thinks our "old level" is 204?

This strange occurrence will teach us something important about both the debugger and how C++ works.

When we stop the debugger on a line of code, the program has been stopped _right before_ that line is about to be executed, meaning the "oldLevel" variable has not been initialized yet.

In C++, uninitialized memory can contain more or less anything, and the number 204 is just arbitrary garbage that don't mean anything to us at this point.

If we move the debugger another step forward, we'll instead get the correct current level of our character:

<img class="mi ili" src="https://i.imgur.com/Sg5GybN.png">

## Inspecting the Callstack

Debugging can also help us understand the order that different functions call each others in our program. In Visual Studio, we can click on the various lines in the Call Stack Window to take us to the previous function that called the one we're currently in.

If we click on the second line from the top in the call stack window, we should be taken to a line inside `cs_character.cpp`, hovering right below the call to the `GiveLevel` function that we were previously in.

_Note: Visual Studio highlights the line **right below** the current function call when traversing the call stack. This can be a little confusing at first_

<img class="mi ili" src="https://i.imgur.com/hzbWSDn.png">



This allow us to inspect even more variables that went into how the current function ended up being called. If we keep scrolling down in the call stack window, we can even get as far back as the programs main function.

<img class="mi ili" src="https://i.imgur.com/zVVg3Lw.png">

### Resuming Execution

When we're done, we can click the green "Continue" button and should see that the game suddenly responds again and levels up our character.

_Note: If you forgot to turn off the freeze detector, it's possible the game instead crashes at this point._

_Note: If you took very long in the debugging session, it's possible the game logs you out_

<img class="mi ili" src="https://i.imgur.com/Qc130p8.png">

<img class="mi ili" src="https://i.imgur.com/ebqMfbC.png">

## Debugging Crashes

By attaching a debugger, we can also cause it to stop execution on unhandled exceptions or crash signals to see what exactly happens when the game crashes. This behavior is enabled by default in Visual Studio for most types of exceptions and crashes, but we can still review our settings in the `Exception Settings` window:

<img class="mi ili" src="https://i.imgur.com/MBNL26n.png">

Here's how the code window might look when the game encounters a crash, the only difference to when we suspend on a breakpoint is that there's usually a little box that details the exact exception that occurred, but otherwise we can inspect variables and the callstack just like before.

_This crash was caused by me on purpose by just smashing in a bunch of random garbage into the games memory, so there's no point in trying to analyze it_

<img class="mi ili" src="https://i.imgur.com/v1wiIg3.png">

## Advanced Breakpoints

In the previous section, we learnt how to use basic breakpoints to stop the execution of the worldserver when the player gains a level.

For more complicated scenarios where we might want some more control over when and how exactly a breakpoint should activate, we can _Right-click_ into the left sidebar instead of left-clicking to bring up the menu of _Advanced Breakpoints_. These are, in order:

- Conditional Breakpoints: A breakpoint that allow us to enter in an expression that decides if the breakpoint should activate when stepped on or not.

- Tracepoint: A breakpoint that will print out a message to the debug console instead of stopping the program.

- Temporary Breakpoint: A breakpoint that will only stop the program once, and then automatically remove itself.

- Dependend Breakpoint: A breakpoint that can behave like multiple of the above types of breakpoints at the same time, and offers some even more advanced configurations.

<img class="mi ili" src="https://i.imgur.com/55lSU3z.png">

### Conditional Breakpoints

If we select the same line as before and instead insert a _Conditional Breakpoint_, the following window should appear.

<img class="mi ili" src="https://i.imgur.com/5fp5M5z.png">

This allows us to type in a valid C++ expression where we can make our breakpoint depend on the values of variables in the program. Let's make it so that our breakpoint only fires when the new level set is 5.

Once we've finished entering the expression we want to check, we can close the breakpoint settings window.

<img class="mi ili" src="https://i.imgur.com/pjMQO6K.png">

Now, we can keep leveling up our character ingame using the `.levelup 1` command, and should see that the program only actually stops when the player is about to reach level 5.

<img class="mi ili" src ="https://i.imgur.com/s30JFWO.png">

Conditional breakpoints are sometimes a great alternative to recompiling the core when we need to check very specific things, but still have their limitation. For example, calling functions in our expression is not allowed, even when they are const, and it is sometimes necessary to recompile so we can write checks that only check variables directly.

<img class="mi ili" src = "https://i.imgur.com/J9IrsJG.png">

### Tracepoints

Tracepoints are a type of breakpoints that prints out a message instead of stopping execution. Creating them is as simple as conditional breakpoints, we just right-click the left sidebar where we would normally create breakpoints and we'll get the following menu pop up

<img class="mi ili" src="https://i.imgur.com/uC2mUxj.png">

Here, we can enter in any message, and include any variables we want to print out inside curly `{}` braces.

<img class="mi ili" src="https://i.imgur.com/GdxYXV5.png">

Now, if we run the `.levelup 1` command again, we should see that the game no longer stops. Instead, we can open up the debuggers `Output` window, and should see the message we specified earlier:

<img class="mi ili" src="https://i.imgur.com/BmF77RS.png">

Tracepoints are another great alternative to recompiling to insert log statements into the source itself, but have similar limitations to conditional breakpoints in that they cannot call functions.