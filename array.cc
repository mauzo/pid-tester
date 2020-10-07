#include <array>
#include <string>
#include <cstdio>
#include <vector>

using namespace std::literals;

class value {
  public:
    float   f;

    value(float f) : f(f) {
        printf("Constructing value %.1f at %x\n", f, (uintptr_t)this);
    }
    ~value() {
        printf("Destructing value %.1f at %x\n", f, (uintptr_t)this);
    }
    value &operator=(value &v) {
        f = v.f;
        printf("Copying value %x -> %x\n", (uintptr_t)&v, (uintptr_t)this);
        return *this;
    }
};

typedef std::array<value, 2> sample;

std::vector<sample> samples;

void
show_sample(const sample *s, const char *msg) {
    printf("Showing sample %s:\n", msg);
    printf("  sample is at %x,", (uintptr_t)s);
    printf("  data is at %x,", (uintptr_t)s->data());
    printf("  sample[0] is at %x\n", (uintptr_t)&(s[0]));
}

sample
build_sample() {
    static float count = 0.0;
    sample  s{count + 0.1, count + 0.2};
    count += 1.0;
    show_sample(&s, "in build_sample");
    return s;
}

void
add_sample(sample s) {
    show_sample(&s, "in add_sample");
    samples.push_back(s);
    show_sample(&(samples.back()), "in vector");
}

void
caller() {
    sample s = build_sample();
    show_sample(&s, "in caller, non-ref");
    add_sample(s);
}

int
main(int argc, char **argv) {
    value *v = new value(99);
    delete v;
    caller();
    caller();

    for (auto &s: samples) {
        show_sample(&s, "in vector in main");
    }
}
