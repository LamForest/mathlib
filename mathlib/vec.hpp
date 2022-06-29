#include <iostream>

using std::ostream;

// namespace mathlib{
    template <typename T, int N, int... indices>
    struct Swizzle{
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;

        /**
         * 在头文件中声明并同时定义constexpr static需要c++1z标准，否则报ld找不到Swizzle::inds错误
         * 如果是pre c++1z，不考虑的constexpr的情况下，static变量需要在头文件中声明，在cpp中定义，详见https://stackoverflow.com/questions/3229883/static-member-initialization-in-a-class-template
         * 如果是pre c++1z, 且要定义constexpr static，我不知道改该怎么办
         */
        constexpr static int inds[] = {indices...}; 

        reference operator[](int index){
            return data[inds[index]];
        }

        
        const_reference operator[](int index) const{
            return data[inds[index]];
        }

        T data[N];
    };

    template <typename T>
    struct vec2
    {
        
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        

        vec2():data{0,0}{};

        vec2(T x, T y):data{x, y}{}

        reference operator[](int index){
            return data[index];
        }

        const_reference operator[](int index) const{
            return data[index];
        }

        reference operator=(const vec2<T> &rhs){
            this->data[0] = rhs.data[0];
            this->data[1] = rhs.data[1];
        }
        union
        {
            T data[2];
            struct {T x;T y;};
            Swizzle<T, 2, 1, 0> yx;
            Swizzle<T, 3, 1, 1, 0> yyx;
            Swizzle<T, 3, 1, 1, 1> yyy;
            Swizzle<T, 3, 0, 0, 0> xxx;
        };
        
    };

    template <typename T>
    ostream& operator<<(ostream&out, const vec2<T>& v){
        out << v[0] << ", " << v[1] << ";" ;
        return out;
    }

// };