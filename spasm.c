/*
 * Copyright (C) 2011, Stefan Hacker <dd0t@users.sourceforge.net>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>

#include "spasm_parser.h"
#include "helpers/elfwrite.h"


int main(int argn, char **argv) {
    const unsigned char rodata[] = {
            0x3e, 0x20, 0x49, 0x6e, 0x76, 0x61, 0x6c, 0x69, 0x64, 0x20,
            0x69, 0x6e, 0x70, 0x75, 0x74, 0x2e, 0x20, 0x50, 0x6c, 0x65,
            0x61, 0x73, 0x65, 0x20, 0x65, 0x6e, 0x74, 0x65, 0x72, 0x20,
            0x61, 0x6e, 0x20, 0x75, 0x6e, 0x73, 0x69, 0x67, 0x6e, 0x65,
            0x64, 0x20, 0x69, 0x6e, 0x74, 0x65, 0x67, 0x65, 0x72, 0x2e,
            0x0a, 0x4e, 0x75, 0x6d, 0x62, 0x65, 0x72, 0x20, 0x74, 0x6f,
            0x6f, 0x20, 0x6c, 0x61, 0x72, 0x67, 0x65, 0x2e, 0x20, 0x4d,
            0x75, 0x73, 0x74, 0x20, 0x62, 0x65, 0x20, 0x73, 0x6d, 0x61,
            0x6c, 0x6c, 0x65, 0x72, 0x20, 0x74, 0x68, 0x61, 0x6e, 0x20,
            0x32, 0x5e, 0x33, 0x32, 0x2e, 0x0a
    };

    const unsigned char text[] = {
            0xb8, 0x04, 0x00, 0x00, 0x00, 0xbb, 0x01, 0x00, 0x00, 0x00,
            0xb9, 0x00, 0x00, 0x00, 0x10, 0xba, 0x02, 0x00, 0x00, 0x00,
            0xcd, 0x80, 0xb8, 0x03, 0x00, 0x00, 0x00, 0xbb, 0x00, 0x00,
            0x00, 0x00, 0xb9, 0x00, 0x00, 0x00, 0x20, 0xba, 0xff, 0x00,
            0x00, 0x00, 0xcd, 0x80, 0x83, 0xf8, 0x01, 0x74, 0xcf, 0xbe,
            0x00, 0x00, 0x00, 0x20, 0x01, 0xf0, 0x31, 0xc0, 0x31, 0xdb,
            0xbf, 0x0a, 0x00, 0x00, 0x00, 0x8a, 0x1e, 0x80, 0xfb, 0x0a,
            0x74, 0x4b, 0x80, 0xfb, 0x30, 0x7c, 0x2b, 0x80, 0xfb, 0x39,
            0x7f, 0x26, 0x80, 0xeb, 0x30, 0xf7, 0xe7, 0x70, 0x07, 0x01,
            0xd8, 0x72, 0x03, 0x46, 0xeb, 0xe1, 0xb8, 0x04, 0x00, 0x00,
            0x00, 0xbb, 0x01, 0x00, 0x00, 0x00, 0xb9, 0x33, 0x00, 0x00,
            0x10, 0xba, 0x2d, 0x00, 0x00, 0x00, 0xcd, 0x80, 0xeb, 0x88,
            0xb8, 0x04, 0x00, 0x00, 0x00, 0xbb, 0x01, 0x00, 0x00, 0x00,
            0xb9, 0x02, 0x00, 0x00, 0x10, 0xba, 0x31, 0x00, 0x00, 0x00,
            0xcd, 0x80, 0xe9, 0x6d, 0xff, 0xff, 0xff, 0xc3, 0xbe, 0xff,
            0x00, 0x00, 0x20, 0xbb, 0x0a, 0x00, 0x00, 0x00, 0xc6, 0x06,
            0x0a, 0x4e, 0x31, 0xd2, 0xf7, 0xf3, 0x83, 0xc2, 0x30, 0x88,
            0x16, 0x4e, 0x83, 0xf8, 0x00, 0x75, 0xf1, 0xb8, 0x04, 0x00,
            0x00, 0x00, 0xbb, 0x01, 0x00, 0x00, 0x00, 0x89, 0xf1, 0x89,
            0xf2, 0x81, 0xea, 0x00, 0x00, 0x00, 0x20, 0xcd, 0x80, 0xc3,
            0xe8, 0x33, 0xff, 0xff, 0xff, 0xe8, 0xc2, 0xff, 0xff, 0xff,
            0xbb, 0x00, 0x00, 0x00, 0x00, 0xb8, 0x01, 0x00, 0x00, 0x00,
            0xcd, 0x80
    };


    const unsigned char data[] = "Nothing useful here";

    FILE *source;
    FILE *target;
    ParserState parser;
    Command *cmd;
    MemoryLocation *mem;
    Label *lbl;
    Errc result;

    if (argn < 3)
    {
        fprintf(stderr, "Usage:\n"
               "    %s [source] [target]\n", argv[0]);
        return EXIT_FAILURE;
    }

    source = fopen(argv[1], "r");
    if (!source)
    {
        fprintf(stderr, "Failed to open source file \"%s\"\n", argv[1]);
        return EXIT_FAILURE;
    }

    init_parser(&parser);
    result = parse_file(&parser, source);
    if (result != ERR_SUCCESS)
    {
        fprintf(stderr, "Failed to parse source file, reason: %s line %u\n",
                SPASM_ERR_STR[result], parser.last_line);

        cleanup_parser(&parser);
        return EXIT_FAILURE;
    }

    printf("Variables:\n");
    mem = parser.memory_location_first;
    while (mem)
    {
        printf("%i $%s %i\n", mem->source_line, mem->name, mem->size);
        mem = mem->next;
    }
    printf("Commands:\n");
    cmd = parser.command_first;
    while (cmd)
    {
        printf("%i %s\n", cmd->source_line, SPASM_MNEMONICS[cmd->type]);
        cmd = cmd->next;
    }

    printf("Labels:\n");
    lbl = parser.label_first;
    while (lbl)
    {
        printf("%i %s\n", lbl->command->source_line, lbl->name);
        lbl = lbl->next;
    }

    cleanup_parser(&parser);
    fclose(source);

    target = fopen(argv[2], "wb");
    if (!target)
    {
        fprintf(stderr, "Failed to open target file \"%s\"\n", argv[2]);
        return EXIT_FAILURE;
    }

    elf_write(target,
            0x8048148,
            0x08048080,
            text, sizeof(text),
            0x10000000,
            rodata, sizeof(rodata),
            0x15000000,
            data, sizeof(data),
            0x20000000,
            0x100);

    fclose(target);

    return EXIT_SUCCESS;
}
