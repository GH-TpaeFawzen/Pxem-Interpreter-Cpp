# Pxem-Interpreter-Cpp
I wanted Pxem interpreter, so I tried making in C++.

# What is Pxem?
**Pxem** was an esonic programming language created by "**ぬこ**" in 2008, but today the language is about to be forgotten. For more details, [see this article.](https://esolangs.org/wiki/Pxem)

# Usage
To use the program,

1. Compile "bringPxemBack.cpp"
2. You will get the interpreter program
3. Run the program, attaching the Pxem file.

If you run like: PROGRAMNAME **-d** PXEMFILENAME, it'll run in debug mode.

# Standardisation
Since official site didn't clarify some specific things about Pxem, I standardisated like below:

* The file's extension must be either `.pxe` or `.pxem`.
* The interpreter cannot read file-path part.
* The interpreter reads from first character to last character of filename.
  * When interpreter recognises `.e`, it'll read the content of file from first to last characters.
  * When it ends reading the content of file, it'll continue reading the character on file-name from next to `.e`.
  * When it finds another `.e` on content of file, it'll read from first-character on content of file.
  * When it finds `.d` on content of file, it'll continue reading the character on file-name from next to `.e`.
* The sum of `.w`, `.x`, `.y`, and `.z` must be equal to that of `.a`.
  * Otherwise, run-time error will occur.
* `.a` must not be put before first `.w`, `.x`, `.y`, or `.z`.
* If the stack is empty when the interpreter reaches to `.w`, `.x`, `.y`, or `.z`, it'll continue reading from next to the corresponding `.a`.
  * If the stack has only a data when the interpreter reaches to `.x`, `.y`, or `.z`, the stack will be empty in addition to above.
* If the stack has only a data when the interpreter reaches `.+`, `.-`, `.!`, `.$`, or `.%`, the content of stack won't be lost.
* `.m` can be done as many times as you'd like, unless temporal-region is empty. In other word, the temporal-region will never be lost.
* When the interpreter executes `.p`, `.o`, or `.n`, it'll output new-line character in addition to the content of the stack.
