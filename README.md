# tester_ft_containers
Tester for level 5 project "ft_containers" @42Tokyo

>  ⚠️ Important notes  : 
> - All functions including  `vector::data()`, `map::at()`, and `reverse_iterator::operator=` need to be implemented for this tester to compile.
> - Not all features are tested

# Usage

## Directory structure
- Expected default directory structure
  ```
  .
  |- ft_containers/
  |- tester_ft_containers/
  ```
- Edit `PATH_TO_YOUR_CONTAINER` in Makefile
  ```Makefile
  # ---------------------------------------------------------------------------- #
  # set path to your ft_container
  
  PATH_TO_YOUR_CONTAINER := ../ft_containers/includes/
  ```

## Run

### Normal Test
```
./grademe.sh
```
##### Individual test 
```
./grademe.sh vector
```

### Benchmark Test
```
make bench
./bench_test
```
##### Individual test 
>  ⚠️ Compilation requires all the containers 
```
./bench_test map
```

# Results

| Result                                                                                                                                                    | Description                                                                |
| --------------------------------------------------------------------------------------------------------------------------------------------------------- | -------------------------------------------------------------------------- |
| <img width="47" alt="SS 2022-05-18 14 11 56" src="https://user-images.githubusercontent.com/60470877/168971708-c0ab7800-564d-4186-b03a-fc8505989d05.png"> | The function passed the test.                                              | 
| <img width="38" alt="SS 2022-05-18 14 25 48 3" src="https://user-images.githubusercontent.com/60470877/168972423-b84bbe3a-8985-4f04-a430-b0f6539ea353.png"> </br><img width="65" alt="SS 2022-05-18 14 50 21" src="https://user-images.githubusercontent.com/60470877/168972299-dde34c7f-5a6f-488f-a0df-44af74480237.png"></br><img width="56" alt="SS 2022-05-18 14 25 48 2 2" src="https://user-images.githubusercontent.com/60470877/168972528-75d11cc6-da1c-4fdf-8dad-860cb97edb2f.png"> | The function failled the test. |
| <img width="81" alt="SS 2022-05-18 14 25 48" src="https://user-images.githubusercontent.com/60470877/168972631-5c9facf3-413a-4dd4-9f67-6361a3eaedde.png"> | The function taking more than 1 second on the test. Considered as timeout. |
| <img width="53" alt="SS 2022-05-18 15 34 00" src="https://user-images.githubusercontent.com/60470877/168973073-514ad5cd-8019-4324-8942-51ed4abbcd30.png"> | The test result differs from std, but the behaviour is undefined.          | 

# Demo

### Normal Test
<img width="673" alt="SS 2022-05-18 14 50 21" src="https://user-images.githubusercontent.com/60470877/168969514-c8cc7aaf-55b8-4a02-93ef-f7e6724ed956.png">

### Benchmark Test
<img width="728" alt="SS 2022-05-18 14 36 47" src="https://user-images.githubusercontent.com/60470877/168969598-46f65267-f35b-413c-b4a1-38a8a2270880.png">

# Reference
- I used the following tester as a reference
- Thank you very much!
- [libft-unit-test](https://github.com/alelievr/libft-unit-test) by [alelievr](https://github.com/alelievr)
