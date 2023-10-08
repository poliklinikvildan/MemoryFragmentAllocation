#include <iostream>
#include <vector>
#include <map>
#include <algorithm> // For sorting

using namespace std;

struct Fragment {
    int startBlock;
    int endBlock;
};

struct Job {
    int jobId;
    int startTime;
    int requiredSize;
    int executionInterval;
    string jobState;
};

void printMemoryState(vector<int>& memory) {
    cout << "Memory State: ";
    for (auto block : memory) {
        cout << block << " ";
    }
    cout << endl;
}

int main() {
    int totalFreeMemorySize = 20; // in KB
    int pageSize = 1; // in KB

    // Job table
    vector<Job> jobTable = {
        {1, 1, 2, 7, "Sleep"},
        {2, 2, 3, 8, "Sleep"},
        {3, 3, 4, 6, "Sleep"},
        {4, 4, 3, 6, "Sleep"},
        {5, 5, 2, 9, "Sleep"},
        {6, 6, 3, 6, "Sleep"},
        {7, 7, 2, 6, "Sleep"}
    };

    // File fragment information
    vector<Fragment> fileFragments = {
        {28, 28}, {5, 5}, {12, 12}, {13, 13}, {1, 1}, {4, 4}
    };

    int fileSize = 8; // in KB
    int diskBlockSize = 1; // in KB
    int totalMemoryBlocks = totalFreeMemorySize / pageSize;

    vector<int> memoryWorst(totalMemoryBlocks, 0);
    vector<int> memoryBest(totalMemoryBlocks, 0);
    vector<int> memoryFirst(totalMemoryBlocks, 0); // First-Fit memory

    map<int, string> timeToOperationMap;

    // Sort file fragments by size in descending order for worst-fit
    sort(fileFragments.begin(), fileFragments.end(), [](const Fragment& a, const Fragment& b) {
        return (a.endBlock - a.startBlock) > (b.endBlock - b.startBlock);
    });

    // Start a loop for memory allocation, reading job table, and file fragments in order
    for (int t = 1; t < 16; t++) {
        // Check if the current time exists in the job table and perform the corresponding operation
        for (auto job : jobTable) {
            if (job.startTime <= t && (job.startTime + job.executionInterval) >= t) {
                timeToOperationMap[job.startTime] = job.jobState;
            }
        }

        // Allocate file fragments using Worst-Fit strategy
        if (t <= 12) {
            cout << "Section 1 (Worst-Fit):" << endl;
            for (auto fragment : fileFragments) {
                int requiredBlocks = (fragment.endBlock - fragment.startBlock + 1) / diskBlockSize;
                int worstFitBlock = -1;
                int largestFreeBlockSize = 0;

                // Find the largest available memory block
                for (int i = 0; i < totalMemoryBlocks; i++) {
                    if (memoryWorst[i] == 0) {
                        int j = i;
                        int freeBlocks = 0;
                        while (j < totalMemoryBlocks && memoryWorst[j] == 0) {
                            freeBlocks++;
                            j++;
                        }
                        if (freeBlocks > largestFreeBlockSize) {
                            worstFitBlock = i;
                            largestFreeBlockSize = freeBlocks;
                        }
                    }
                }

                // Allocate the file fragment to memory if a suitable block is found
                if (worstFitBlock != -1 && largestFreeBlockSize >= requiredBlocks) {
                    for (int i = worstFitBlock; i < worstFitBlock + requiredBlocks; i++) {
                        memoryWorst[i] = fragment.startBlock;
                    }
                    fragment.startBlock += requiredBlocks * diskBlockSize;
                    cout << "Time: " << t << " - Allocation Succeeded for Fragment" << endl;
                } else {
                    cout << "Time: " << t << " - Allocation Failed for Fragment" << endl;
                }
            }
            printMemoryState(memoryWorst);
        }

        // Allocate file fragments using Best-Fit strategy
        if (t > 6 && t <= 12) {
            cout << "Section 2 (Best-Fit):" << endl;
            for (auto fragment : fileFragments) {
                int requiredBlocks = (fragment.endBlock - fragment.startBlock + 1) / diskBlockSize;
                int bestFitBlock = -1;
                int smallestFreeBlockSize = totalMemoryBlocks; // Initialize with a large value

                // Find the smallest available memory block that can accommodate the fragment
                for (int i = 0; i < totalMemoryBlocks; i++) {
                    if (memoryBest[i] == 0) {
                        int j = i;
                        int freeBlocks = 0;
                        while (j < totalMemoryBlocks && memoryBest[j] == 0) {
                            freeBlocks++;
                            j++;
                        }
                        if (freeBlocks >= requiredBlocks && freeBlocks < smallestFreeBlockSize) {
                            bestFitBlock = i;
                            smallestFreeBlockSize = freeBlocks;
                        }
                    }
                }

                // Allocate the file fragment to memory if a suitable block is found
                if (bestFitBlock != -1) {
                    for (int i = bestFitBlock; i < bestFitBlock + requiredBlocks; i++) {
                        memoryBest[i] = fragment.startBlock;
                    }
                    fragment.startBlock += requiredBlocks * diskBlockSize;
                    cout << "Time: " << t << " - Allocation Succeeded for Fragment" << endl;
                } else {
                    cout << "Time: " << t << " - Allocation Failed for Fragment" << endl;
                }
            }
            printMemoryState(memoryBest);
        }

        // Allocate file fragments using First-Fit strategy
        if (t > 8 && t <= 12) {
            cout << "Section 3 (First-Fit):" << endl;
            for (auto fragment : fileFragments) {
                int requiredBlocks = (fragment.endBlock - fragment.startBlock + 1) / diskBlockSize;
                int firstFitBlock = -1;

                // Find the first available memory block that can accommodate the fragment
                for (int i = 0; i < totalMemoryBlocks; i++) {
                    if (memoryFirst[i] == 0) {
                        int j = i;
                        int freeBlocks = 0;
                        while (j < totalMemoryBlocks && memoryFirst[j] == 0) {
                            freeBlocks++;
                            j++;
                        }
                        if (freeBlocks >= requiredBlocks) {
                            firstFitBlock = i;
                            break;
                        }
                    }
                }

                // Allocate the file fragment to memory if a suitable block is found
                if (firstFitBlock != -1) {
                    for (int i = firstFitBlock; i < firstFitBlock + requiredBlocks; i++) {
                        memoryFirst[i] = fragment.startBlock;
                    }
                    fragment.startBlock += requiredBlocks * diskBlockSize;
                    cout << "Time: " << t << " - Allocation Succeeded for Fragment" << endl;
                } else {
                    cout << "Time: " << t << " - Allocation Failed for Fragment" << endl;
                }
            }
            printMemoryState(memoryFirst);
        }

        if (timeToOperationMap.find(t) != timeToOperationMap.end()) {
            // Perform the corresponding operation based on job state
            string jobState = timeToOperationMap[t];
            cout << "Time: " << t << " - Job State: " << jobState << endl;
        }
    }

    return 0;
}
