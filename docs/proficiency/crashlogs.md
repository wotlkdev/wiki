---
layout: default
title: Server Crashlogs (Unfinished)
nav_order: 4
---

# Server Crashlogs (Unfinished)

So you've finally brought together that complicated patch into your server, you hit the bat file to start your worldserver and are immediately met with the message:

```
Process error code 3221225477
```

The server has crashed. What now?

If the servers own crash handler was invoked correctly, it should have produced two files into a folder called `Crashes` in the same folder as your `worldserver.exe`. The filenames should contain a timestamp of when the crash occurred, one `.txt` file and one `.dmp` file.

_Note for TSWoW Users: This 'Crashes' directory is instead stored in the root of your TSWoW installation._

## Sending these files to the developer

If you have installed someone elses script and are not yourself proficient with C++ source code, it may be wise to just pass these files on to someone who can read them.

If possible, it may be good to compile your server in **debug mode** for these files to be as useful as possible. Sometimes **RelWithDebInfo** is good enough, but especially for the `.dmp` file, debug mode will give more interesting information for the developer to look at.

## Crash Files: The text file

The text file will contain a few few different sections, but we actually only care about one. That is the section that begins with the text:

```
Call stack:
```

This is what's known as a "stack trace", or "call stack". It's a list of addresses that represents the hierarchy of functions that the server was executing at the time of the crash.

For example, let's pretend we have the following program in a file called `my_program.cpp`:

```c++
void inner_function()
{
    // some code here causing a crash
    throw std::runtime_error("Let's crash the program");
}

void outer_function()
{
    inner_function();
}

// program entrypoint
int main()
{
    outer_function();
}
```

If we pretend that we also had some kind of magical 'crash handler' in this program, we could end up with a call stack as follows:

```
Call stack:
Address           Frame             Function              SourceFile
00007FFA2B320B1F  00000036BDB3AD70  void inner_function   my_program.cpp line 4
00007FFA2B320AEA  00000036BDB3ADC0  void outer_function   my_program.cpp line 8
00007FFA2B320AA4  00000036BDB3ADF0  int main              my_program.cpp line 14
*
```

The columns we're interested in are the "Function" and "SourceFile" columns. We can see that we are in a program state where the "main" function called the "outer_function", which itself called the "inner_function", and we even get the exact row in the source code the program crashed. For this trivial program this is only telling us the obvious, but this is extremely useful for a larger program where we don't know why it crashed.

Let's look at a real example: [Link](./real_crashlog.txt)

This is significantly messier than our trivial example, and a lot of these function names don't seem to make any sense.

What we can start by doing is to look at the `SourceFile` columns. You will notice that the first few lines point at some file called `xmemory`. This is an internal header file for the microsoft STL, and is not part of our code. It's unlikely there would be something wrong with these files, so what we're instead looking for is the first line that actually points to a file that we own.

We find this on the sixth row:

```
D:\dev\wow\tswow-maintenance\tswow\cores\TrinityCore\src\server\game\Entities\Object\Object.h line 354
```

This points to `Object.h` in our emulator code, which is a very common file as it handles the root class for all kinds of entities in the game. The function it specifies is `WorldObject::SetName`, and if we open our emulator and take a look at this function, we'll get the following:

```c++
void SetName(std::string const& newname) { m_name = newname; }
```

This is a very minimal function and not much can go wrong with it unless we've done something very naughty with C++. There is **one** common thing that cause a function like this to crash, and that's if the object we're trying to set the name of doesn't exist.

If we look at the (fictional) code that called this function in our script, we might have something like this:

```c++
Player* player = some_valid_player(...);
player->GetSelection()->SetName("Current Selection");
```

This is problematic code, because players don't always have a unit selected. What caused our server to crash was probably a player trying to run this renaming scheme without having a selection, and so the program crashes when it tries to set the name of an object that doesn't exist. For completion, a fixed code that doesn't crash would look like:

```c++
Player* player = some_valid_player(...);
if(Unit* unit = player->GetSelection())
{
    unit->SetName("Current Selection");
}
else
{
    // handle case where unit doesn't exist
}
```

## The "dump" file

TODO