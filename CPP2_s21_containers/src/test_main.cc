#include "array/test_array.cc"
#include "avl_tree/test_tree.cc"
#include "list/test_list.cc"
#include "map/test_map.cc"
#include "multiset/test_multiset.cc"
#include "queue/test_queue.cc"
#include "set/test_set.cc"
#include "stack/test_stack.cc"
#include "vector/test_vector.cc"

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
