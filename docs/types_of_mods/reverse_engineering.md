---
layout: default
title: Retroporting
nav_order: 8
---

# Reverse Engineering

Reverse engineering refers to figuring out how an obfuscated system in the game 'works' to allow us to understand, replicate or modify it for our purposes. Almost everything we are able to mod in the game today is based on people in the past reverse engineering the games binary file formats and network protocol.

Today, a very large portion of these files and protocols is already documented for WoTLK, and thus we no longer need to 'reverse engineer' them. Instead, reverse engineers have shifted their focus to the client binary (wow.exe) itself and how to modify its internal code. The purposes for doing this varies, from fixing annoying bugs and driver issues to unlocking custom behavior otherwise impossible.

Reverse engineering is one of the most technically difficult aspects of wow modding, and requires a good understanding of how computer code and memory works, as well as reading x86 assembly code and using disassemblers like IDA or Ghidra.

<table class="gt" style="table-layout: fixed; width: 100%;">
    <tr>
        <td><p><img class="mi" src="https://i.imgur.com/pAm6mJF.png">010 Editor: Tool used to inspect and edit binary file formats.</p></td>
        <td><p><img class="mi" src="https://i.imgur.com/FPdXcHP.png">IDA Pro: Tool used to inspect and edit binary file formats.</p></td>
    </tr>
    <tr>
        <td><p><img class="mi" src="https://i.imgur.com/UeuTU2M.png">10 classes per race limitation caused by wow.exe bug solved by reverse engineering.</p></td>
    </tr>
</table>