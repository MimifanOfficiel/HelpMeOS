#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <limine.h>

#include "includes/keyboardhandler.h"

// Set the base revision to 2, this is recommended as this is the latest
// base revision described by the Limine boot protocol specification.
// See specification for further info.

__attribute__((used, section(".requests")))
static volatile LIMINE_BASE_REVISION(2);

// The Limine requests can be placed anywhere, but it is important that
// the compiler does not optimise them away, so, usually, they should
// be made volatile or equivalent, _and_ they should be accessed at least
// once or marked as used with the "used" attribute as done here.

__attribute__((used, section(".requests")))
static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

// Finally, define the start and end markers for the Limine requests.
// These can also be moved anywhere, to any .c file, as seen fit.

__attribute__((used, section(".requests_start_marker")))
static volatile LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".requests_end_marker")))
static volatile LIMINE_REQUESTS_END_MARKER;



// Halt and catch fire function.
static void hcf(void) {
    for (;;) {
#if defined (__x86_64__)
        asm ("hlt");
#elif defined (__aarch64__) || defined (__riscv)
        asm ("wfi");
#elif defined (__loongarch64)
        asm ("idle 0");
#endif
    }
}


// Fonction pour écrire un octet dans un port
static inline void outb(uint16_t port, uint8_t data) {
    asm volatile ("outb %0, %1" : : "a"(data), "Nd"(port));
}



// The following will be our kernel's entry point.
// If renaming kmain() to something else, make sure to change the
// linker script accordingly.
void kmain(void) {
    // Ensure the bootloader actually understands our base revision (see spec).
    if (LIMINE_BASE_REVISION_SUPPORTED == false) {
        hcf();
    }

    // Ensure we got a framebuffer.
    if (framebuffer_request.response == NULL
     || framebuffer_request.response->framebuffer_count < 1) {
        hcf();
    }

    // Fetch the first framebuffer.
    struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];

    // Effacer l'écran pour le noir
    volatile uint32_t *fb_ptr = framebuffer->address;
    for (size_t i = 0; i < framebuffer->height; i++) {
        for (size_t j = 0; j < framebuffer->width; j++) {
            fb_ptr[i * (framebuffer->pitch / sizeof(uint32_t)) + j] = 0x000000; // Noir
        }
    }

    // Dessiner le texte
    draw_string(framebuffer, "Welcome to HelpMe OS\n"
    "This system have been developped by Lila BRANDON in 2024\n"
    "contact@lilabrandon.fr  |  https://lilabrandon.fr\n"
    "Type 'exit' to stop your system\n", 0x0058FF00); // Couleur verte
    start_y = start_y + 8*5;
    
    // Gérer le clavier
    handle_keyboard(framebuffer);


    // We're done, just hang...
    hcf();
}
