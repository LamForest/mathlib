#include <iostream>

using std::ostream;

// namespace mathlib{
    template <typename T, int N, int... indices>
    struct Swizzle{
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;

        using self_type = Swizzle<T, N, indices...>;
        using self_reference = self_type &;
        using self_const_reference = const self_type &;
        
        /**
         * 在头文件中声明并同时定义constexpr static需要c++1z标准，否则报ld找不到Swizzle::inds错误
         * 如果是pre c++1z，不考虑的constexpr的情况下，static变量需要在头文件中声明，在cpp中定义，详见https://stackoverflow.com/questions/3229883/static-member-initialization-in-a-class-template
         * 如果是pre c++1z, 且要定义constexpr static，目前不清楚怎么做
         */
        constexpr static int inds[] = {indices...}; 

        reference operator[](int index){
            return data[inds[index]];
        }
        
        const_reference operator[](int index) const{
            return data[inds[index]];
        }
        /*
            编译期报错, 维度不匹配
        */
        template <int ...rhs_indices>
        self_reference operator=(const Swizzle<T, N, rhs_indices...>& rhs){
            auto &lhs = *this;
            for(int i = 0; i < N; ++i){
                lhs[i] = rhs[i];
            }
            return *this;
        }
        

        T data[N];
    };

    template <typename T>
    struct vec2
    {
        
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;

        using self_type = vec2<T>;
        using self_reference = vec2<T> &;
        using self_const_reference = const vec2<T> &;

        constexpr static int DIM = 2; //必须放在前面
        

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
            return *this;
        }

        template <int ...indices> //template <int T, int M, int ...indices> 是错误的写法
        /**
         * DIM的定义必须放在前面，否则编译期实例化此函数时无法找到DIM定义
         * */
        self_reference operator=(const Swizzle<T, DIM, indices...> & rhs){
            for(int i = 0; i < DIM; ++i){
                this->data[i] = rhs[i];
            }
            return *this;
        }

        

        union
        {
            T data[2];
            struct {T x;T y;};
            Swizzle<T, 2, 0, 1> xy;
            Swizzle<T, 2, 0, 0> xx;
            Swizzle<T, 2, 1, 0> yx;
            Swizzle<T, 2, 1, 1> yy;
            Swizzle<T, 3, 0, 0, 0> xxx;
            Swizzle<T, 3, 0, 0, 1> xxy;
            Swizzle<T, 3, 0, 1, 0> xyx;
            Swizzle<T, 3, 0, 1, 1> xyy;

            Swizzle<T, 3, 1, 0, 0> yxx;
            Swizzle<T, 3, 1, 0, 1> yxy;
            Swizzle<T, 3, 1, 1, 0> yyx;
            Swizzle<T, 3, 1, 1, 1> yyy;

            // Swizzle<T, 3, 0, 0, 0> ;
        };
        
    };

    template <typename T>
    ostream& operator<<(ostream&out, const vec2<T>& v){
        out << v[0] << ", " << v[1] << ";" ;
        return out;
    }

// };