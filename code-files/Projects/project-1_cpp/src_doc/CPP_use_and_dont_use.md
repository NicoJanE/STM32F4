### Can Use No Problem (C++-Specific Features for Embedded Systems)

| **Feature**                                   | **Recommendation**                        |
|-----------------------------------------      |----------------------------------         |
| **Simple Classes (No Virtual Functions)**     | Use (encapsulation without overhead)      |
| **`std::array` (Fixed Size)**                 | Use (fixed size, no dynamic allocation)   |
| **Inline Functions**                          | Use (efficient for small functions)       |
| **`constexpr` for Compile-Time Constants**    | Use (reduce runtime overhead)             |
| **Function Pointers**                         | Use (alternative to virtual functions)    |

---

### Try Limited Usage (C++ Features with Careful Consideration)

| **Feature**                                                   | **Reason**                                      |
|-----------------------------------------                      |----------------------------------               |
| **`std::cout` and I/O Streams**                               | Avoid using for output in embedded systems due to potential performance hits. If needed, use very simple custom I/O or redirect to UART/other hardware.   |
| **`std::thread` (Concurrency)**                               | Limited usage only if **RTOS** or similar environment is available. Without an OS, threading (including C11 threading) is not typically supported.        |
| **`std::mutex`, `std::lock_guard` (Thread Synchronization)**  | Only use with an **RTOS** (see above). Not applicable in a non-threaded environment.                                                                      |
| **Templates (Complex/Deep Hierarchy)**                        | Use templates sparingly, especially when they involve large amounts of code generation or recursion. Too much metaprogramming can increase code size and complexity. |
| **Type Traits (`std::is_integral`, `std::enable_if`)**        | Can be powerful for compile-time checks, but they can increase complexity and code size.                                                                  |
| **C++ Standard Library Algorithms**                           | Can be used if the system's resources are sufficient, but make sure the libraries don't rely on dynamic memory allocation or unnecessary overhead.        |

---

### Absolutely Avoid (C++ Features to Avoid in Embedded Systems)

| **Feature**                                       | **Reason**                            |
|-----------------------------------------          |----------------------------------     |
| **Dynamic Memory Allocation (`new`, `delete`)**   | Use of heap memory can lead to fragmentation and unpredictable behavior in embedded systems with limited memory.                  |
| **`std::vector`**                                 | Uses dynamic memory allocation, which is not suitable for embedded systems with strict memory requirements.                       |
| **`std::map`, `std::unordered_map`**              | These containers require dynamic memory allocation and can be inefficient for small, constrained systems.                         |
| **`std::string`**                                 | String manipulation in C++ relies on dynamic memory and might not be feasible for embedded systems.                               |
| **Virtual Functions**                             | Introduces runtime overhead due to vtables and can result in larger code size and slower execution.                               |
| **`std::unique_ptr`, `std::shared_ptr`**          | These features introduce complexity, dynamic memory allocation, and potential overhead that are undesirable in embedded systems.  |
| **Exceptions**                                    | Exception handling introduces runtime overhead and may complicate the control flow, which is problematic in embedded systems.     |
| **Run-time Type Information (RTTI)**              | RTTI (used for `typeid`, `dynamic_cast`) adds overhead and increases code size. It is often unnecessary in embedded systems.      |

---
