/*
 * gpio.cpp
 *
 *  Created on: 2024/08/06
 *      Author: sakur
 */
#include"gpio.hpp"

GpioPin::GpioPin(GPIO_TypeDef* GPIOx,PinName Pin)
:GPIOx(GPIOx),
 Pin(Pin){}

GpioPin::GpioPin(GPIO_TypeDef* GPIOx,PinName Pin,PinMode Mode,PinPull Pull,PinSpeed Speed,PinAlternate Alternate)
:GPIOx(GPIOx),
 Pin(Pin){
	this->configure(Mode,Pull,Speed,Alternate);
}

void GpioPin::configure(PinMode Mode,PinPull Pull,PinSpeed Speed,PinAlternate Alternate){
	/*HAL_GPIO_Init*/
	uint32_t position = 0x00U;
	uint32_t iocurrent;
	uint32_t temp;

	/* Check the parameters */
	assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
	assert_param(IS_GPIO_PIN(Pin));
	assert_param(IS_GPIO_MODE(Mode));

	while (((Pin) >> position) != 0U)
	  {
	    /* Get current io position */
	    iocurrent = (Pin) & (1UL << position);

	    if (iocurrent != 0x00u)
	    {
	      /*--------------------- GPIO Mode Configuration ------------------------*/
	      /* In case of Output or Alternate function mode selection */
	      if(((Mode & GPIO_MODE) == MODE_OUTPUT) ||
	         ((Mode & GPIO_MODE) == MODE_AF))
	      {
	        /* Check the Speed parameter */
	        assert_param(IS_GPIO_SPEED(Speed));
	        /* Configure the IO Speed */
	        temp = GPIOx->OSPEEDR;
	        temp &= ~(GPIO_OSPEEDR_OSPEED0 << (position * 2U));
	        temp |= (Speed << (position * 2U));
	        GPIOx->OSPEEDR = temp;

	        /* Configure the IO Output Type */
	        temp = GPIOx->OTYPER;
	        temp &= ~(GPIO_OTYPER_OT0 << position) ;
	        temp |= (((Mode & OUTPUT_TYPE) >> OUTPUT_TYPE_Pos) << position);
	        GPIOx->OTYPER = temp;
	      }

	      if ((Mode & GPIO_MODE) != MODE_ANALOG)
	      {
	        /* Check the Pull parameter */
	        assert_param(IS_GPIO_PULL(Pull));

	        /* Activate the Pull-up or Pull down resistor for the current IO */
	        temp = GPIOx->PUPDR;
	        temp &= ~(GPIO_PUPDR_PUPD0 << (position * 2U));
	        temp |= ((Pull) << (position * 2U));
	        GPIOx->PUPDR = temp;
	      }

	      /* In case of Alternate function mode selection */
	      if ((Mode & GPIO_MODE) == MODE_AF)
	      {
	        /* Check the Alternate function parameters */
	        assert_param(IS_GPIO_AF_INSTANCE(GPIOx));
	        assert_param(IS_GPIO_AF(Alternate));

	        /* Configure Alternate function mapped with the current IO */
	        temp = GPIOx->AFR[position >> 3U];
	        temp &= ~(0xFU << ((position & 0x07U) * 4U));
	        temp |= ((Alternate) << ((position & 0x07U) * 4U));
	        GPIOx->AFR[position >> 3U] = temp;
	      }

	      /* Configure IO Direction mode (Input, Output, Alternate or Analog) */
	      temp = GPIOx->MODER;
	      temp &= ~(GPIO_MODER_MODE0 << (position * 2U));
	      temp |= ((Mode & GPIO_MODE) << (position * 2U));
	      GPIOx->MODER = temp;

	      /*--------------------- EXTI Mode Configuration ------------------------*/
	      /* Configure the External Interrupt or event for the current IO */
	      if ((Mode & EXTI_MODE) != 0x00u)
	      {
	        /* Enable SYSCFG Clock */
	        __HAL_RCC_SYSCFG_CLK_ENABLE();

	        temp = SYSCFG->EXTICR[position >> 2U];
	        temp &= ~(0x0FUL << (4U * (position & 0x03U)));
	        temp |= (GPIO_GET_INDEX(GPIOx) << (4U * (position & 0x03U)));
	        SYSCFG->EXTICR[position >> 2U] = temp;

	        /* Clear Rising Falling edge configuration */
	        temp = EXTI->RTSR1;
	        temp &= ~(iocurrent);
	        if ((Mode & TRIGGER_RISING) != 0x00U)
	        {
	          temp |= iocurrent;
	        }
	        EXTI->RTSR1 = temp;

	        temp = EXTI->FTSR1;
	        temp &= ~(iocurrent);
	        if ((Mode & TRIGGER_FALLING) != 0x00U)
	        {
	          temp |= iocurrent;
	        }
	        EXTI->FTSR1 = temp;

	        temp = EXTI->EMR1;
	        temp &= ~(iocurrent);
	        if ((Mode & EXTI_EVT) != 0x00U)
	        {
	          temp |= iocurrent;
	        }
	        EXTI->EMR1 = temp;

	        /* Clear EXTI line configuration */
	        temp = EXTI->IMR1;
	        temp &= ~(iocurrent);
	        if ((Mode & EXTI_IT) != 0x00U)
	        {
	          temp |= iocurrent;
	        }
	        EXTI->IMR1 = temp;
	      }
	    }

	    position++;
	  }
}

void GpioPin::deconfigure(){
	  uint32_t position = 0x00U;
	  uint32_t iocurrent;
	  uint32_t tmp;

	  /* Check the parameters */
	  assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
	  assert_param(IS_GPIO_PIN(Pin));

	  /* Configure the port pins */
	  while ((Pin >> position) != 0U)
	  {
	    /* Get current io position */
	    iocurrent = (Pin) & (1UL << position);

	    if (iocurrent != 0x00u)
	    {
	      /*------------------------- EXTI Mode Configuration --------------------*/
	      /* Clear the External Interrupt or Event for the current IO */

	      tmp = SYSCFG->EXTICR[position >> 2U];
	      tmp &= (0x0FUL << (4U * (position & 0x03U)));
	      if (tmp == (GPIO_GET_INDEX(GPIOx) << (4U * (position & 0x03U))))
	      {
	        /* Clear EXTI line configuration */
	        EXTI->IMR1 &= ~(iocurrent);
	        EXTI->EMR1 &= ~(iocurrent);

	        /* Clear Rising Falling edge configuration */
	        EXTI->FTSR1 &= ~(iocurrent);
	        EXTI->RTSR1 &= ~(iocurrent);

	        tmp = 0x0FUL << (4U * (position & 0x03U));
	        SYSCFG->EXTICR[position >> 2U] &= ~tmp;
	      }

	      /*------------------------- GPIO Mode Configuration --------------------*/
	      /* Configure IO in Analog Mode */
	      GPIOx->MODER |= (GPIO_MODER_MODE0 << (position * 2u));

	      /* Configure the default Alternate Function in current IO */
	      GPIOx->AFR[position >> 3u] &= ~(0xFu << ((position & 0x07u) * 4u));

	      /* Deactivate the Pull-up and Pull-down resistor for the current IO */
	      GPIOx->PUPDR &= ~(GPIO_PUPDR_PUPD0 << (position * 2u));

	      /* Configure the default value IO Output Type */
	      GPIOx->OTYPER  &= ~(GPIO_OTYPER_OT0 << position);

	      /* Configure the default value for IO Speed */
	      GPIOx->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED0 << (position * 2u));
	    }

	    position++;
	  }
}

void GpioPin::exti_config(IRQn_Type irqn){
	HAL_NVIC_SetPriority(irqn,0,0);
	HAL_NVIC_EnableIRQ(irqn);
}

void GpioPin::all_gpio_init(){
	/*__HAL_RCC_GPIOx_CLKENABLE*/
	uint32_t tmpreg;
	SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOAEN);
	SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOBEN);
	SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOCEN);
	SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIODEN);
	SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOEEN);
	SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOFEN);
	SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOGEN);

	tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOAEN);
	UNUSED(tmpreg);
	tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOBEN);
	UNUSED(tmpreg);
	tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOCEN);
	UNUSED(tmpreg);
	tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIODEN);
	UNUSED(tmpreg);
	tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOEEN);
	UNUSED(tmpreg);
	tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOFEN);
	UNUSED(tmpreg);
	tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOGEN);
	UNUSED(tmpreg);
}

GPIO_PinState GpioPin::readpin(){
	  GPIO_PinState bitstatus;

	  /* Check the parameters */
	  assert_param(IS_GPIO_PIN(Pin));

	  if ((GPIOx->IDR & Pin) != 0x00U)
	  {
	    bitstatus = GPIO_PIN_SET;
	  }
	  else
	  {
	    bitstatus = GPIO_PIN_RESET;
	  }
	  return bitstatus;
}

void GpioPin::writepin(GPIO_PinState PinState){
	  /* Check the parameters */
	  assert_param(IS_GPIO_PIN(GPIO_Pin));
	  assert_param(IS_GPIO_PIN_ACTION(PinState));

	  if (PinState != GPIO_PIN_RESET)
	  {
	    GPIOx->BSRR = (uint32_t)Pin;
	  }
	  else
	  {
	    GPIOx->BRR = (uint32_t)Pin;
	  }
}

void GpioPin::operator=(GPIO_PinState PinState){
	  /* Check the parameters */
	  assert_param(IS_GPIO_PIN(GPIO_Pin));
	  assert_param(IS_GPIO_PIN_ACTION(PinState));

	  if (PinState != GPIO_PIN_RESET)
	  {
	    GPIOx->BSRR = (uint32_t)Pin;
	  }
	  else
	  {
	    GPIOx->BRR = (uint32_t)Pin;
	  }
}

void GpioPin::operator=(int s){
	if(s == 0){
		this->operator=(GPIO_PIN_RESET);
	}
	else{
		this->operator =(GPIO_PIN_SET);
	}
}

void GpioPin::operator=(bool f){
	if(f){
		this->operator=(GPIO_PIN_SET);
	}
	else{
		this->operator=(GPIO_PIN_RESET);
	}
}

void GpioPin::togglepin(){
	  uint32_t odr;

	  /* Check the parameters */
	  assert_param(IS_GPIO_PIN(Pin));

	  /* get current Output Data Register value */
	  odr = GPIOx->ODR;

	  /* Set selected pins that were at low level, and reset ones that were high */
	  GPIOx->BSRR = ((odr & Pin) << GPIO_NUMBER) | (~odr & Pin);
}

void GpioPin::on(){
	*(this) = GPIO_PIN_SET;
}

void GpioPin::off(){
	*(this) = GPIO_PIN_RESET;
}

HAL_StatusTypeDef GpioPin::lockpin(){
	  __IO uint32_t tmp = GPIO_LCKR_LCKK;

	  /* Check the parameters */
	  assert_param(IS_GPIO_LOCK_INSTANCE(GPIOx));
	  assert_param(IS_GPIO_PIN(Pin));

	  /* Apply lock key write sequence */
	  tmp |= Pin;
	  /* Set LCKx bit(s): LCKK='1' + LCK[15-0] */
	  GPIOx->LCKR = tmp;
	  /* Reset LCKx bit(s): LCKK='0' + LCK[15-0] */
	  GPIOx->LCKR = Pin;
	  /* Set LCKx bit(s): LCKK='1' + LCK[15-0] */
	  GPIOx->LCKR = tmp;
	  /* Read LCKK register. This read is mandatory to complete key lock sequence */
	  tmp = GPIOx->LCKR;

	  /* read again in order to confirm lock is active */
	  if ((GPIOx->LCKR & GPIO_LCKR_LCKK) != 0x00u)
	  {
	    return HAL_OK;
	  }
	  else
	  {
	    return HAL_ERROR;
	  }
}

uint32_t GpioPin::pin(){
	return this->Pin;
}
