#ifndef TEST_BENCH_HPP
#define TEST_BENCH_HPP

template<int size, int n_ops = 2>
class test_bench : public sc_module
{
public:
  sc_in<sc_bv<size>> input;
  sc_in<bool> clk_in;

  sc_out<sc_bv<n_ops>> operation;
  sc_out<sc_bv<size>> a_out;
  sc_out<sc_bv<size>> b_out;


  test_bench(const sc_module_name& nm) : sc_module(nm)
  {
    SC_THREAD(test);
    sensitive << clk_in.pos();
  }
private:
  SC_HAS_PROCESS(test_bench);

  void print()
  {
    if(operation.read().to_uint())
      std::cout << a_out.read().to_uint();
    else std::cout << a_out.read().to_string();
    switch (operation.read().to_uint())
    {
      default:
      case 0:
      case 1:
        std::cout << " + ";
        break;

      case 2:
        std::cout << " - ";
        break;

      case 3:
        std::cout << " * ";
        break;
    }

    if(operation.read().to_uint())
      std::cout << b_out.read().to_uint();
    else std::cout << b_out.read().to_string();
    std::cout << " = ";

    switch (operation.read().to_uint())
    {
      case 0:
        std::cout << input.read().to_string();
        break;

      default:
      case 1:
        std::cout << input.read().to_uint();
        break;

      case 2:
      case 3:
        std::cout << input.read().to_int();
        break;
    }
    std::cout << std::endl;
  }

  void test()
  {
    std::cout << "A o B = R" << std::endl;

    a_out.write(3);
    b_out.write(7);
    operation.write(1);
    wait();
    print();

    a_out.write(3);
    b_out.write(7);
    operation.write(3);
    wait();
    print();

    a_out.write(3);
    b_out.write(7);
    operation.write(2);
    wait();
    print();

    a_out.write(3);
    b_out.write(7);
    operation.write(0);
    wait();
    print();

    sc_stop();
  }
};
#endif
