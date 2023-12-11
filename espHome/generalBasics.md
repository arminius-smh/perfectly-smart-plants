General Basics
===

# Before you start

## Rescourses
- Raspberry Pi is it should run free
- PC if you just want to test

# Setup

1. I reccomend creating a keepass for the project specific passwords, there will be quite some
2. Choose setup method & follow the responding guide
    - [VM](./setupVM.md): i cant recommend, difficult with network bridge
    - [Docker](./setupDocker.md): very easy to setup, very quick. Good for testing, not good for day to day usage, as it requires the pc to be running
    - Raspberry Pi: Good for stable day to day usage, but pricy in setting up, especially if you are not sure its the right thing for you
3. Test to see if you can access the website

# First Steps

1. Create User in the HA Dashboard, save the credentials in the keepass
2. Make yourself familiar with the dashboard


# Adding ESP's
Follow First the [ESP Doku](./espDoku.md).

An ESP alone is not enough, we also wan't to add [Components](./Components/componentsDoku.md).

To Actually see and use those, we need to follow the [ESP Doku](./espDoku.md) again.

# Dashboard
Finally, to see or use the components we added, we configure the [Dashboard](./dashboard.md) to our needs.