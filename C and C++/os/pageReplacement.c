#include <stdio.h>

int main() {
    int numPages, numFrames, i, j, pageFaults = 0, currentIndex = 0;
    
    // printf("Enter the number of pages in the page reference string: ");
    scanf("%d", &numPages);
    
    int pageString[numPages];
    
    // printf("Enter the page reference string: ");
    for (i = 0; i < numPages; i++) {
        scanf("%d", &pageString[i]);
    }
    
    // printf("Enter the number of frames: ");
    scanf("%d", &numFrames);
    
    int frameArray[numFrames]; 
    // int framePresent[numFrames];
    
    // printf("Enter the frame array: ");
    for (i = 0; i < numFrames; i++) {
        scanf("%d", &frameArray[i]);
        // framePresent[i] = 0;
    }
    
    int pageFound = 0, faults[numFrames];
    
    for (i = 0; i < numPages; i++) {
        pageFound = 0;
        
        for (j = 0; j < numFrames; j++) {
            if (pageString[i] == frameArray[j]) {
                pageFound = 1;
                break;
            }
        }
        
        if (pageFound == 0) {
            faults[currentIndex] = frameArray[currentIndex];
            frameArray[currentIndex] = pageString[i];
            pageFaults++;
            currentIndex = (currentIndex + 1) % numFrames;
        }
    }
    
    printf("The number of page faults: [");
    for (i = 0; i < numFrames - 1; i++) {
        printf("%d, ", faults[i]);
    }
    printf("%d]\n", faults[numFrames - 1]);
    
    return 0;
}
