#include <fstream>

using namespace std;

template <typename H>
class MaxHeap
{
   public:
      MaxHeap()
      {
         heap = NULL;
         heapsize = 0;
         heapifyCount = 0;
      }

      void buildMaxHeap(H *array, int n)
      {
         heap = new H[n + 1];
         for(int i = 1; i < n + 1; i++)
            heap[i] = array[i];
         heapsize = n;
         for(int i = heapsize/2; i > 0; i--)
            maxHeapify(i);
      }

      void extractMax()
      {
         if(heapsize)
         {
            heap[1] = heap[heapsize--];
            if(heapsize)
               maxHeapify(1);
         }
      }

      void print(ofstream &out)
      {
         out << heapifyCount << endl;
      }

   private:
      H *heap;
      int heapsize;
      int heapifyCount;

      void maxHeapify(int i)
      {
         heapifyCount++;
         int left = i << 1;
         int right = (i << 1) | 1;
         int max = -1;
         if(left <= heapsize && heap[left] > heap[i])
            max = left;
         else
            max = i;
         if(right <= heapsize && heap[right] > heap[max])
            max = right;
         if(max != i)
         {
            H temp = heap[i];
            heap[i] = heap[max];
            heap[max] = temp;
            maxHeapify(max);
         }
      }
};

template <typename H>
void manager(ifstream &in, ofstream &out, H &valore)
{
   int n;
   in >> n;

   H array[n + 1];
   for(int i = 1; i < n + 1; i++)
      in >> array[i];

   MaxHeap<H> maxHeap;
   maxHeap.buildMaxHeap(array, n);
   for(int i = 0; i < n; i++)
      maxHeap.extractMax();
   maxHeap.print(out);
}

int main()
{
   ifstream in("input.txt");
   ofstream out("output.txt");

   char lettera;
   double numero;

   for(int i = 0; i < 100; i++)
   {
      string tipo;
      in >> tipo;

      if(tipo == "char")
         manager(in, out, lettera);
      else
         manager(in, out, numero);
   }

   return 0;
}
