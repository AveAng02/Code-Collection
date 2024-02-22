from threading import Semaphore, Thread

class H2O:
    def __init__(self):
        self.hydrogen_semaphore = Semaphore(2)
        self.oxygen_semaphore = Semaphore(1)
        self.barrier_semaphore = Semaphore(0)

    def releaseHydrogen(self):
        self.hydrogen_semaphore.release()
        self.check_and_release()

    def releaseOxygen(self):
        self.oxygen_semaphore.release()
        self.check_and_release()

    def check_and_release(self):
        self.barrier_semaphore.acquire()
        if self.hydrogen_semaphore._value >= 2 and self.oxygen_semaphore._value >= 1:
            self.hydrogen_semaphore.acquire()
            self.hydrogen_semaphore.acquire()
            self.oxygen_semaphore.acquire()

            # Release threads to form a water molecule
            self.barrier_semaphore.release()
            self.hydrogen_semaphore.release()
            self.hydrogen_semaphore.release()
            self.oxygen_semaphore.release()

def bond_hydrogen(h2o):
    h2o.releaseHydrogen()

def bond_oxygen(h2o):
    h2o.releaseOxygen()

def create_water_molecule(water):
    h2o = H2O()

    threads = []
    for molecule in water:
        if molecule == 'H':
            threads.append(Thread(target=bond_hydrogen, args=(h2o,)))
        elif molecule == 'O':
            threads.append(Thread(target=bond_oxygen, args=(h2o,)))

    for thread in threads:
        thread.start()

    for thread in threads:
        thread.join()

# Example usage
water = "HOH"
create_water_molecule(water)
