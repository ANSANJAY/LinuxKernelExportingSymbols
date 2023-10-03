**Section 1: Explain the technical concept**

📘 **Symbol**:

In the realm of programming, a **symbol** refers to an identifier that stands for either 
- data storage (like variables) or 
- sequences of instructions to execute (like functions).
- Symbols are essentially names given to these particular memory addresses so we can easily reference and manipulate them.

📘 **Symbol Table**:

- A **symbol table** is a specialized data structure crafted by the compiler, storing a list of all the symbols utilized in a given program. 
- For the Linux kernel, every built image has an accompanying symbol table. This table is typically found at `/boot/System.map-<linux_version>`, giving you a map of all the kernel symbols' names and their corresponding memory addresses.

PWD : /boot/

![](./Screenshot%20from%202023-10-02%2019-05-59.png)

- Navigate to  `/boot/System.map-<linux_version>` 
- For example : `System.map-6.2.15-100.fc36.x86_64`
- **Only for the built in kernel module**

![](./Screenshot%20from%202023-10-02%2019-04-41.png)

📘 **Exporting Symbols**:

In the Linux kernel, when a new function or variable is declared within a module, it remains local to that module by default. To make it accessible to other modules, you need to **export** it. You have the option to use either `EXPORT_SYMBOL` or `EXPORT_SYMBOL_GPL` based on licensing needs.

📘 **Difference between EXPORT_SYMBOL and EXPORT_SYMBOL_GPL**:

- `EXPORT_SYMBOL`: Allows any kernel module, irrespective of its licensing, to use the exported symbol.
  
- `EXPORT_SYMBOL_GPL`: Restricts usage of the exported symbol only to modules that are GPL licensed.

📘 **Difference between System.map and /proc/kallsyms**:

- **System.map**: This is a symbol table that contains symbols only for the kernel's built-in modules.
  
The command you ran:

```sh
wc -l System.map-6.2.15-100.fc36.x86_64
```

with the output:

```sh
202876 System.map-6.2.15-100.fc36.x86_64
```

indicates that there are **202,876** symbols in the `System.map` file for the Linux kernel version `6.2.15-100.fc36.x86_64`. 

### Context:

- **System.map:** This file maps symbols (function and variable names) to their addresses in memory and is used for debugging and understanding kernel behavior. A specific `System.map` file is typically generated each time the kernel is compiled and is associated with that particular kernel version (hence `6.2.15-100.fc36.x86_64` in the filename).

### Significance:

- **Symbol Count Discrepancy:** The difference in symbol count between `/proc/kallsyms` and `System.map` could be due to several reasons, such as different kernel versions or configurations, or additional modules being loaded (in the case of `/proc/kallsyms`).

- **Use in Debugging:** Much like `/proc/kallsyms`, the `System.map` file is pivotal in debugging kernel issues. If the system panics, having the appropriate `System.map` for the running kernel can help developers symbolically decode stack traces and understand the context of the crash.

### Comparison to `/proc/kallsyms`:

- **Dynamic vs. Static:** While `/proc/kallsyms` can dynamically change (e.g., when modules are loaded or unloaded, reflecting the current running kernel), `System.map` is static, representing the symbols available at the time the kernel was built.

- **Accessibility:** `/proc/kallsyms` usually provides more access to symbols even without the necessity of `System.map` being present, making it especially useful in various live environments.

### Additional Notes:

- **Kernel Debugging:** For kernel debugging, ensure you are using the correct `System.map` for your running kernel. Using a mismatched `System.map` can cause incorrect symbol resolution.

- **Kernel Development:** Developers and kernel hackers often refer to these symbol tables and map files to verify function and variable addresses, ensuring their modifications or modules interact correctly with the kernel.

The symbol count and the specific symbols present would depend on the configuration options chosen when the kernel was compiled and can vary between different kernels and distributions. So, the counts being different between different `System.map` files or between `System.map` and `/proc/kallsyms` are expected.

- **/proc/kallsyms**: This contains symbols for both the kernel's built-in modules and the dynamically loaded modules. It provides a broader view of symbols present in the running kernel.

When you run the command:

```sh
wc -l /proc/kallsyms
```

I get the output:

```sh
293231 /proc/kallsyms
```

This means there are **293,231** symbols in the kernel symbol table at the time the command was run. Each line in `/proc/kallsyms` represents a single symbol.

### Explanation:

- **Symbols:** In the context of computing and programming, symbols refer to named entities used to identify various elements such as functions, variables, etc., in a program (or in this case, the Linux kernel).

- **/proc/kallsyms:** The file `/proc/kallsyms` provides a view into the kernel's symbol table, which maps addresses to symbol names. It is particularly useful for debugging and development purposes. Each line in this file represents one symbol and typically consists of the following three columns:
  - **Address:** The memory address of the symbol.
  - **Type:** A single character that indicates the type or scope of the symbol (e.g., "T" for text/execute sections, "D" for initialized data section, etc.).
  - **Name:** The name of the symbol.

So, `293,231` symbols signify that the kernel, along with its loaded modules, has this many named entities (like functions and variables) available and usable at that point in time.

### Importance:

- **Debugging:** Developers and system administrators utilize the symbols for debugging kernel crashes and issues. For instance, if the kernel panics, it may log an address which can be looked up in `/proc/kallsyms` to identify the function or variable involved in the crash.
  
- **Development:** For developers, especially those working on kernel modules or diving into kernel development, this table aids in understanding and exploring the kernel's functions and data structures.

- **Profiling & Tracing:** Symbols are also crucial for various profiling and tracing tools to correlate addresses to human-readable function names and provide meaningful output.

The exact number of symbols can vary based on the kernel version, configuration, and loaded modules since each of these factors can introduce additional symbols.

![](./Screenshot%20from%202023-10-02%2019-13-25.png)

---

**Curiousity**

❓ **Question 1**: Why might a developer choose to use `EXPORT_SYMBOL_GPL` over `EXPORT_SYMBOL`?

📝 **Answer**: A developer might use `EXPORT_SYMBOL_GPL` to ensure that the exported symbol is only used by modules that adhere to the GPL license. This can help in maintaining the open-source ethos and prevent proprietary modules from utilizing certain critical or sensitive functionalities.

❓ **Question 2**: How can one symbol be present in both `System.map` and `/proc/kallsyms`? 

📝 **Answer**:
-  A symbol will appear in both `System.map` and `/proc/kallsyms` if it's part of the kernel's built-in modules. 
- While `System.map` only contains built-in module symbols, `/proc/kallsyms` includes those along with symbols from dynamically loaded modules.

❓ **Question 3**: What happens if two modules export the same symbol name?

📝 **Answer**: If two modules try to export the same symbol name, it will lead to a conflict. When you try to insert the second module that exports the already exported symbol, the kernel will prevent it from being loaded, and an error will be reported.

---

**Section 3: Simplify the concept**

💡 **In Simple Words**:

Imagine you're in a library 📚:

1. **Symbols**: Think of symbols as the titles of books and journals. Each title represents a specific set of information (data or instructions).

2. **Symbol Table**: This is like the library's catalog system, listing all the titles available and where to find them.

3. **Exporting Symbols**: Suppose you've written a new book and want to make it available to others. Exporting is like adding your book to the library's collection, so others can read it. But you can choose who gets to read it: everyone (`EXPORT_SYMBOL`) or only those with a special membership (`EXPORT_SYMBOL_GPL`).

4. **System.map vs. /proc/kallsyms**: It's like having two catalog systems. One (`System.map`) only lists the permanent collection of the library, while the other (`/proc/kallsyms`) lists both the permanent collection and the new arrivals or temporary exhibits.



------


📘 **/proc/kallsyms and Kernel Symbols**:

The `/proc/kallsyms` file represents the kernel's symbol table. It's a virtual file that gives you insight into the kernel space symbols. It contains the memory addresses of functions, variables, and other symbols, along with their types and names. When developers add or export a new symbol to the kernel, it should be visible in this file.

By using the `cat` command combined with `grep`, you can quickly check if a particular symbol, in this case `print_jiffies`, exists within the kernel's symbol table.

![](./Screenshot%20from%202023-09-19%2021-44-40.png)
![](./Screenshot%20from%202023-09-19%2021-45-01.png)

---


❓ **Question 1**: What is the significance of the `/proc/kallsyms` file?

📝 **Answer**: The `/proc/kallsyms` file provides a list of all symbols (like functions and variables) used within the kernel, including both built-in and dynamically loaded module symbols. This allows for debugging, profiling, and other kernel-related investigations.

❓ **Question 2**: What would it indicate if `print_jiffies` is not found when you grep `/proc/kallsyms`?

📝 **Answer**: If `print_jiffies` isn't found in `/proc/kallsyms`, it might indicate that the module or kernel component exporting this symbol hasn't been loaded, the symbol hasn't been exported properly, or the symbol doesn't exist.

❓ **Question 3**: Are there any other methods to search for a kernel symbol besides using `/proc/kallsyms`?

📝 **Answer**: Yes, another common method to check for kernel symbols is to use the `System.map` file, typically located in `/boot/`. However, `System.map` only lists symbols for the built-in modules of the kernel, whereas `/proc/kallsyms` also includes dynamically loaded modules.

---


💡 **In Simple Words**:

Imagine you've got a massive puzzle 🧩 with each piece representing a function or variable in the Linux kernel. Now, `/proc/kallsyms` is like the reference picture on the puzzle box. It shows you every piece and where it fits. If you're looking for a specific puzzle piece, like `print_jiffies`, you'd check this reference picture to see if it's there. Using the `cat` and `grep` commands is like using a magnifying glass 🔍 to find that specific piece in the picture! If you don't find it, maybe that piece hasn't been added to the puzzle yet.


