template <class T>
class ObjectPool {
   public:
    T* Allocate();
    T* TryAllocate();

    void Deallocate(T* object);

    ~ObjectPool();

   private:
    ...
};