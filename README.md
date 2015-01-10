dEXEcute
========

About the Project:
==================

The dEXEcute Project is about creating a computer completely from scratch in software. Nothing will be implemented in hardware, instead everything will be emulated. Its emphasis is not on having a great architecture, being fast, feature-rich or anything like that but to be simple. Very simple. So simple that it will be pretty much useless, except for the experience that I will gain with this project. The simplicity also makes this project realistic. The project started out as a self-designed simple CPU only. But what good is a cpu that has only been designed but doesn't exist in any way? So I added an emulator. But what good is a cpu with its emulator if there aren't any tools so I can write machine code for it? So I added an assembler. But what good is a cpu with its emulator and the ability to program it if there's  no way for input or output? So I added an emulated keyboard and display. But what good is.... etc. etc. So eventually it became a computer.

Goals:
======
The end-goal will be to have an emulated computer designed completely from scratch with everything designed and implemented both simple and the way I feel like. Since that's quite a task, it'll be divided into several milestones:

Milestone 1:	Version 0.1.0	Completion State: 50% 
- Design the CPU with as few instructions, registers and features as possible		- DONE.
- Write an assembler that can turn assembly source code into machine code that the designed CPU can execute.		-DONE
- Write a minimalist emulator that emulates the CPU, RAM and ROM. No input/output of any kind yet.

Milestone 2: (Featurelist can change)
- Add support for interrupts
- Add a display and keyboard to the emulator

Milestone X:
- Write an emulator where cpu clock speed can be adjusted, even down to 1 instruction per second, or 1 instruction per keypress. Visuals include: ROM data, RAM data, registers, info about interrupts etc. Generally as much info about the system as possible so that people can learn and see how the computer works. This could even be expanded (by me or anybody else) by writing tutorials etc. that would guide people smoothly into the topic of how computers, CPUs etc. really work without having to deal with all the complexity that our modern computers with x86 architecture etc. have. I think the simplicity with which everything in the project will be designed and built would really aid in that.

Purpose of this project:
========================

The main purpose is for me personally to learn how computers work on the low-level side of things. And how to design and emulate them. That alone is enough for me. I have already learned a lot of stuff while working on this and I've just begun.
A nice bonus would be if anyone interested in the topic would find this project helpful with learning and for that I will try to add comments into the code and documentation as good as I can.
