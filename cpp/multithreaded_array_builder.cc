/**
 *  "I implemented some toy script to make use of multi-threaded programming to
 *  generate and process a million lists
 *  >Python : 30s
 *  >Rust: 2.2s
 *  >Go: couldn't actually use 4 cores even with GOMAXPROCS, I killed it after 2
minutes"
 *
 *
 *  Go version:
 *
 *      import (
 *          "fmt"
 *          "math/rand"
 *          "runtime"
 *          "sync"
 *          "time"
 *      )
 *
 *      func main() {
 *          fmt.Printf("Starting to drop\n")
 *
 *          runtime.GOMAXPROCS(4)
 *          start := time.Now()
 *          const numberOfRuns = 10000
 *          const numberOfWorkers = 4
 *          var waitingGroup sync.WaitGroup
 *          waitingGroup.Add(numberOfRuns)
 *          results := make(chan bool)
 *
 *          for range make([]int, numberOfRuns) {
 *              go dropTheBall(results, &waitingGroup)
 *          }
 *          redCount := 0
 *          counter := 0
 *          for element := range results {
 *              if element == false {
 *                  redCount++
 *              }
 *              counter++
 *              if counter >= numberOfRuns {
 *                  close(results)
 *                  break
 *              }
 *          }
 *          waitingGroup.Wait()
 *
 *          elapsed := time.Since(start)
 *          fmt.Println(redCount, "/", numberOfRuns)
 *          fmt.Printf("Achieved in %v \n", elapsed)
 *      }
 *
 *      func dropTheBall(resultChannel chan bool, waitingGroup *sync.WaitGroup)
{
 *          defer waitingGroup.Done()
 *          list := generateList()
 *          var previousWasBlue bool = false
 *          for {
 *              var listLength int32 = int32(len(list))






*              if len(list) <= 1 {
 *                  resultChannel <- list[0]
 *                  break
 *              }
 *              rand.Seed(time.Now().UnixNano())
 *              index := rand.Int31n(listLength)
 *              if previousWasBlue {
 *                  list = remove(list, int64(index))
 *                  previousWasBlue = false
 *              } else {
 *                  switch list[index] {
 *                  // blue/true balls trigger the next one to be discarded
 *                  case true:
 *                      previousWasBlue = true
 *                  // red/false balls are discarded on the spot
 *                  case false:
 *                      list = remove(list, int64(index))
 *                  }
 *              }
 *          }
 *      }
 *
 *      func generateList() []bool {
 *
 *          total := make([]bool, 100)
 *          for index := range make([]int, 20) {
 *              total[index] = true
 *          }
 *          return total
 *      }
 *
 *      func remove(list []bool, index int64) []bool {
 *          return append(list[:index], list[index+1:]...)
 *      }
 *
 *
 *
 *  Rust version:
 *
 *      use rand::Rng;
 *      use std::time::{Instant};
 *      use std::sync::mpsc;
 *      use threadpool::ThreadPool;
 *
 *      fn main() {
 *          println!("This starts here");
 *          let now = Instant::now();
 *
 *          let n_workers = 4;
 *          let n_jobs = 1000000;
 *          let pool = ThreadPool::new(n_workers);
 *          let (tx, rx) = mpsc::channel();
 *
 *          for _ in 0..n_jobs {
 *              let tx = tx.clone();
 *              pool.execute(move|| {
 *                  tx.send(draw()).unwrap();
 *              });
 *          }
 *
 *          let mut count = 0;
 *          let mut red_count = 0;
 *          for received in rx {
 *              if received == false {
 *                  red_count += 1
 *              }
 *              count += 1;
 *              if count >= n_jobs {
 *                  break
 *              }
 *          }
 *          println!("{:?}", now.elapsed());
 *          println!("__");
 *          println!("{}/{}", red_count, n_jobs);
 *      }
 *
 *
 *      fn setup() -> Vec<bool> {
 *          // generate a list of 20 blue balls and 80 red
 *          let mut list: Vec<bool> = Vec::new();
 *          let mut counter = 0;
 *          while counter < 100 {
 *              if counter <= 80 {
 *                  list.push(false); // red
 *              } else {
 *                  list.push(true); //blue
 *              }
 *              counter +=1
 *          }
 *          list
 *      }
 *
 *      fn draw() -> bool {
 *
 *          let mut list = setup();
 *          let mut previous_was_blue = false;
 *          loop {
 *              if list.len() <= 1 {
 *                  return list[0];
 *              }
 *
 *              let random = rand::thread_rng().gen_range(0, list.len());
 *              match (previous_was_blue, list[random]) {
 *                  (true, _) => {
 *                      list.remove(random);
 *                      previous_was_blue = false
 *                  },
 *                  (false, true) => {
 *                      previous_was_blue = true;
 *                  },
 *                  (false, false) => {
 *                      list.remove(random);
 *                  }
 *              }
 *          }
 *      }
 *
 *
 *  Python version:
 *
 *      import random
 *      from multiprocessing import Process, Pool
 *      from datetime import datetime
 *
 *      def setup():
 *  	red = [False for ball in range(80)]
 *  	blue = [True for ball in range(20)]
 *  	return blue + red
 *
 *      def drop_the_ball(*args):
 *  	all = setup()
 *  	previous_was_blue = False
 *  	while len(all) > 1:
 *  	    index = random.randint(0, len(all) -1)
 *  	    if previous_was_blue:
 *  		del all[index]
 *  		previous_was_blue = False
 *  	    else:
 *  		if all[index]:
 *  		    previous_was_blue = True
 *  		else:
 *  		    del all[index]
 *  	return all[0]
 *
 *      if __name__ == "__main__":
 *
 *  	start = datetime.now()
 *  	results = []
 *  	iterations = 1000000
 *
 *  	# for _ in tqdm(range(iterations)):
 *  	#     ball = drop_the_ball()
 *  	#     results.append(ball)
 *  	with Pool(processes=4) as pool:
 *  	    results = pool.map(drop_the_ball, range(iterations))
 *  	    drop_the_ball()
 *
 *  	    final_red = 0
 *  	    for item in results:
 *  		if item == False:
 *  		    final_red +=1
 *  	    print('{}/{} = {}'.format(final_red, iterations,
final_red/iterations))
 *  	end = datetime.now()
 *  	print(end-start)
 *
 *
 */
#include <assert.h>
#include <stdlib.h>
#include <sys/random.h>

#include <atomic>
#include <chrono>
#include <iostream>
#include <limits>
#include <thread>
#include <vector>

enum class BallColor {
  RED,
  BLUE,
};

auto drop_the_ball(const uint32_t* const random_numbers,
                   const size_t random_number_index) -> BallColor;

auto generate_list() -> std::vector<BallColor>;

void linux_random(uint32_t* const dest, const size_t n);

int main(int /*unused*/, char** /*unused*/) {
  std::cout << "Starting to drop" << std::endl;

  // time starts here
  auto start_time = std::chrono::system_clock::now();

  std::atomic<uint32_t> red_ball_counter{0};
  constexpr size_t NUM_RUNS = 1'000'000'000;
  constexpr size_t NUM_WORKERS = 4;
  assert(NUM_RUNS % NUM_WORKERS == 0);

  // all the random numbers upfront from /dev/random on Linux
  std::vector<uint32_t> random_numbers{};
  random_numbers.resize(NUM_RUNS);
  linux_random(random_numbers.data(), random_numbers.size());

  std::vector<std::thread> threads{};
  threads.reserve(NUM_WORKERS);
  for (auto i = 0; i < NUM_WORKERS; ++i)
    threads.emplace_back(std::thread{
        [&red_ball_counter, &random_numbers, i, NUM_RUNS, NUM_WORKERS]() {
          for (auto j = 0; j < NUM_RUNS / NUM_WORKERS; ++j)
            red_ball_counter +=
                drop_the_ball(random_numbers.data(),
                              i * NUM_RUNS / NUM_WORKERS + j) == BallColor::RED;
        }});
  for (auto& t : threads) t.join();
  // time ends here
  auto end_time = std::chrono::system_clock::now();
  std::cout << red_ball_counter.load() << " / " << NUM_RUNS << std::endl;
  std::cout << "Achieved in "
            << std::chrono::duration_cast<std::chrono::milliseconds>(end_time -
                                                                     start_time)
                   .count()
            << "ms" << std::endl;
  return EXIT_SUCCESS;
}

auto drop_the_ball(const uint32_t* const random_numbers,
                   const size_t random_number_index) -> BallColor {
  auto list = generate_list();
  bool previous_was_blue = false;
  for (auto list_length = list.size(); list_length > 1;
       list_length = list.size()) {
    const auto index = random_numbers[random_number_index] % list_length;
    auto it = list.begin() + index;
    if (previous_was_blue) {
      list.erase(it);
      previous_was_blue = false;
    } else {
      switch (*it) {
        case BallColor::BLUE:
          previous_was_blue = true;
          break;
        case BallColor::RED:
          list.erase(it);
          break;
      }
    }
  }
  return list[0];
}

auto generate_list() -> std::vector<BallColor> {
  std::vector<BallColor> list{100UL};
  for (size_t i = 0; i < 80; ++i) list[i] = BallColor::RED;
  for (size_t i = 80; i < list.size(); ++i) list[i] = BallColor::BLUE;
  return list;
}

void linux_random(uint32_t* const dest, const size_t n) {
  int count = 0;
  do {
    count += ::getrandom(dest, n, GRND_RANDOM);
  } while (count < n);
}
