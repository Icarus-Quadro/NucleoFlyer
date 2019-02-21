#include <mbed.h>
#include <rtos.h>

#include <array>
#include <vector>

constexpr auto kGreenLedId   = LED1;
constexpr auto kBlueLedId    = LED2;
constexpr auto kRedLedId     = LED3;
constexpr auto kUserButtonId = BUTTON1;

struct SRF05 {
    SRF05(PinName trigger, PinName echo):
    trigger_(trigger), echo_(echo){
        echo_.rise(this, &SRF05::rising);
        echo_.fall(this, &SRF05::falling);
        ticker_.attach(this, &SRF05::startRange, 0.1);
    }

    float read() {
        return (dist_);
    }

    operator float() {
        return read();
    }

private:
    DigitalOut trigger_;
    InterruptIn echo_;
    Timer timer_;
    Ticker ticker_;
    float dist_;

    void rising() {
        timer_.reset();
        timer_.start();
    }

    void falling() {
        timer_.stop();
        dist_ = timer_.read_us() * 330.f / 2000000.f;
    }

    void startRange() {
        trigger_ = 1;
        wait_us(20);
        trigger_ = 0;
    }
};

extern "C" int main();

int main() {
    PwmOut blueLed(kBlueLedId);
    blueLed.period(0.01f);
    auto srf = SRF05(PB_8, PB_9);
    for(;;) {
        const auto distance = srf.read();
        printf("Distance: %.1f\n\r", distance);
        blueLed.write(distance);
        Thread::wait(100);
    }
    return 0;
}
