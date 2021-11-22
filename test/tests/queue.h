#define Q_SIZE 5

void push_help(Lists::Queue<int> *queue)
{
    for (uint8_t i = 1; i <= Q_SIZE; i++)
        queue->push(i);

    queue->print();
    queue->printItems();
}

// ? Test Queue push normal
void test_queue_push()
{
    Lists::Queue<int> queue = Lists::Queue<int>(Q_SIZE);

    for (uint8_t i = 1; i <= Q_SIZE; i++)
    {
        TEST_ASSERT_EQUAL(true, queue.push(i));
        queue.printItems();
    }
}

// ? Test Queue push when queue is full
void test_queue_push_full()
{
    Lists::Queue<int> queue = Lists::Queue<int>(Q_SIZE);

    push_help(&queue);

    TEST_ASSERT_EQUAL(false, queue.push(Q_SIZE + 1));
}

// ? Test Queue pop normal
void test_queue_pop()
{
    Lists::Queue<int> queue = Lists::Queue<int>(Q_SIZE);

    push_help(&queue);

    for (uint8_t i = 1; i <= Q_SIZE; i++)
    {
        TEST_ASSERT_EQUAL(i, queue.pop());
        queue.printItems();
    }
}

// ? Test Queue pop when queue is empty
void test_queue_pop_empty()
{
    Lists::Queue<int> queue = Lists::Queue<int>(Q_SIZE);

    TEST_ASSERT_EQUAL(0, queue.pop());
    queue.printItems();
}

// ? Test Queue pop with no paremeter (first item)
void test_queue_pop_index()
{
    Lists::Queue<int> queue = Lists::Queue<int>();

    push_help(&queue);

    TEST_ASSERT_EQUAL(1, queue.pop_index());

    queue.printItems();
}

// ? Test Queue pop in the middle of queue
void test_queue_pop_index_middle()
{
    Lists::Queue<int> queue = Lists::Queue<int>(Q_SIZE);

    push_help(&queue);

    TEST_ASSERT_EQUAL(3, queue.pop_index(2));
    queue.printItems();
}

// ? Test Queue pop in the middle of queue
void test_queue_pop_index_end()
{
    Lists::Queue<int> queue = Lists::Queue<int>(Q_SIZE);

    push_help(&queue);

    TEST_ASSERT_EQUAL(Q_SIZE, queue.pop_index(Q_SIZE - 1));
    queue.printItems();
}

// ? Test Queue front and back
void test_queue_front_back()
{
    Lists::Queue<int> queue = Lists::Queue<int>(Q_SIZE);

    for (uint8_t i = 1; i < Q_SIZE; i++)
    {
        queue.push(i);

        TEST_ASSERT_EQUAL(1, queue.front());

        TEST_ASSERT_EQUAL(i, queue.back());
    }
}

// ? Test Queue size
void test_queue_size()
{
    Lists::Queue<int> queue = Lists::Queue<int>(Q_SIZE);

    TEST_ASSERT_EQUAL(0, queue.size());

    queue.push(10);

    TEST_ASSERT_EQUAL(1, queue.size());

    queue.push(11);

    TEST_ASSERT_EQUAL(2, queue.size());

    queue.pop();

    TEST_ASSERT_EQUAL(1, queue.size());

    queue.pop();

    TEST_ASSERT_EQUAL(0, queue.size());

    queue.pop();

    TEST_ASSERT_EQUAL(0, queue.size());
}

void test_queue()
{
    // Test push
    RUN_TEST(test_queue_push);
    RUN_TEST(test_queue_push_full);

    // Test pop
    RUN_TEST(test_queue_pop);
    RUN_TEST(test_queue_pop_empty);

    // Test pop index
    RUN_TEST(test_queue_pop_index);
    RUN_TEST(test_queue_pop_index_middle);
    RUN_TEST(test_queue_pop_index_end);

    // Test front & back
    RUN_TEST(test_queue_front_back);

    // Test size
    RUN_TEST(test_queue_size);
}
