// Parts of a file from teacher as part of the assignment files we recieved. https://perara.notion.site/IKT218-Advanced-Operating-Systems-2024-bfa639380abd46389b5d69dcffda597a?p=83eabc342fd24b88b00733a78b5a86e0&pm=s
extern "C"{
    #include "memory/memory.h"
    #include "libc/stdio.h"
    #include "pit.h"
    #include "song/song.h"
    #include "terminal.h"
    #include "funzies.h"
}

// Existing global operator new overloads
void* operator new(size_t size) {
    return malloc(size);
}

void* operator new[](size_t size) {
    return malloc(size);
}

// Existing global operator delete overloads
void operator delete(void* ptr) noexcept {
    free(ptr);
}

void operator delete[](void* ptr) noexcept {
    free(ptr);
}

// Add sized-deallocation functions
void operator delete(void* ptr, size_t size) noexcept {
    (void)size; // Size parameter is unused, added to match required signature
    free(ptr);
}

void operator delete[](void* ptr, size_t size) noexcept {
    (void)size; // Size parameter is unused, added to match required signature
    free(ptr);
}


extern "C" int kernel_main(void);
int kernel_main(){
    terminalPrint("Triggering interrupts\n\n");
    asm volatile ("int $0x0");
    asm volatile ("int $0x1");
    asm volatile ("int $0x2");
    
    terminalPrint("\nAllocating some memory\n");
    terminalPut('\n');

    void* some_memory = malloc(12345); 
    void* memory2 = malloc(54321); 
    void* memory3 = malloc(13331);
    char* memory4 = new char[1000]();

    sleep_interrupt(2000);
    terminalClear();
    
    free(some_memory);
    free(memory2);
    free(memory3);
    delete[] memory4;
    terminalPrint("Freed up some memory\n");
    terminalPrint("Allocating some memory for songs\n");
    terminalPut('\n');

    Song* songs[] = {
        new Song({charge_theme, sizeof(charge_theme) / sizeof(Note)}),
    };
    uint32_t n_songs = sizeof(songs) / sizeof(Song*);
    
    terminalPut('\n');

    SongPlayer* player = create_song_player();

    sleep_interrupt(2000);
    terminalClear();
    terminalPut('\n');
    splashScreen(); // From Funzies
    terminalPut('\n');

    for(uint32_t i =0; i < n_songs; i++){
        printf("Playing Song...\n");
        player->play_song(songs[i]);
        printf("Finished playing the song.\n");
    }
    delete player;
    
    terminalPut('\n');

    terminalSetColor(11, 0);
    HelloWorld("HelloWorld(\"print\");\n");
    
    while(true) {}
    return 0;
}
