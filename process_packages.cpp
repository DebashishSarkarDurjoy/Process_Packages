#include <iostream>
#include <queue>
#include <vector>

struct Request {
    Request(int arrival_time, int process_time):
        arrival_time(arrival_time),
        process_time(process_time)
    {}

    int arrival_time;
    int process_time;
};

struct Response {
    Response(bool dropped, int start_time):
        dropped(dropped),
        start_time(start_time)
    {}

    bool dropped;
    int start_time;
};

class Buffer {
public:
    Buffer(int size):
        size_(size),
        finish_time_(),
        counter(0),
        requestQ(),
        isFirst(true)
    {}

    void Store(const Request &request) {
        // write your code here
        if (counter <= size_ - 1) {
          requestQ.push(request);
        }
    }

    std:: vector<Response> Process() {
      std::vector<Response> responsesQ;
      while(!requestQ.empty()) {
        if (isFirst) {
          Response response(false, requestQ.front().arrival_time);
          responsesQ.push_back(response);
          finish_time_.push(requestQ.front().process_time);
          requestQ.pop();
          isFirst = false;
        }
        else if ( requestQ.front().arrival_time >= finish_time_.front() ) {
          Response response(false, requestQ.front().arrival_time);
          responsesQ.push_back(response);
          finish_time_.push(finish_time_.front() + requestQ.front().process_time);
          requestQ.pop();
        }
        else {
          Response response(true, requestQ.front().arrival_time);
          responsesQ.push_back(response);
          requestQ.pop();
        }
      }
      return responsesQ;
    }
private:
    int size_;
    std::queue <int> finish_time_;
    std::queue <Request> requestQ;
    int counter;
    bool isFirst;
};

std::vector <Request> ReadRequests() {
    std::vector <Request> requests;
    int count;
    std::cin >> count;
    for (int i = 0; i < count; ++i) {
        int arrival_time, process_time;
        std::cin >> arrival_time >> process_time;
        requests.push_back(Request(arrival_time, process_time));
    }
    return requests;
}

std::vector <Response> ProcessRequests(const std::vector <Request> &requests, Buffer *buffer) {
    std::vector <Response> responses;
    for (int i = 0; i < requests.size(); ++i)
        //responses.push_back(buffer->Process(requests[i]));
        buffer->Store(requests[i]);

    responses = buffer->Process();
    return responses;
}

void PrintResponses(const std::vector <Response> &responses) {
    for (int i = 0; i < responses.size(); ++i)
        std::cout << (responses[i].dropped ? -1 : responses[i].start_time) << std::endl;
}

int main() {
    int size;
    std::cin >> size;
    std::vector <Request> requests = ReadRequests();

    Buffer buffer(size);
    std::vector <Response> responses = ProcessRequests(requests, &buffer);

    PrintResponses(responses);
    return 0;
}
